#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) { cin >> p[i]; p[i]--; }
    // For each pair (i,j), find max d(i,j) by sorting a subarray
    // d(i,j) = max position difference after sorting one subarray [l,r]
    // After sorting [l,r], positions are sorted. The max distance between
    // positions i and j depends on whether they're in the sorted range.
    //
    // Key insight: for pair (i,j) with values p[i], p[j]:
    // Without sorting: distance = |i - j|
    // After sorting [l,r]: if both i,j in [l,r], their new positions are
    // determined by their rank among values in [l,r].
    //
    // For each pair (i,j), the max distance is achieved by choosing l,r
    // such that p[i] and p[j] are pushed to opposite ends of [l,r].
    // Specifically, choose l,r so that:
    // - l = position of (rank of p[i] in [l,r]) - 1
    // - r = position of (rank of p[j] in [l,r])
    // The max distance = r - l.
    //
    // For pair (i,j) with p[i] < p[j]:
    // After sorting [l,r], p[i] goes to position l + (rank of p[i] in [l,r]) - 1
    // and p[j] goes to position l + (rank of p[j] in [l,r]) - 1.
    // Distance = rank(p[j]) - rank(p[i]).
    // To maximize: choose [l,r] to include as many values between p[i] and p[j]
    // as possible, but also push them to the edges.
    //
    // Actually, the max distance for pair (i,j) is:
    // max over all valid [l,r] of |new_pos(i) - new_pos(j)|
    // where new_pos(i) = l + (number of elements in [l,r] with value <= p[i]) - 1
    // (or similar for the sorted order).
    //
    // For n=3000, we can try all O(n^2) pairs and for each, try all O(n^2) subarrays.
    // That's O(n^4) which is too slow.
    //
    // Better approach: for each pair (i,j), the max distance is:
    // If we sort [l,r] where l <= min(i,j) and r >= max(i,j):
    // new_pos(i) = l + count(x in [l,r] : p[x] <= p[i]) - 1
    // new_pos(j) = l + count(x in [l,r] : p[x] <= p[j]) - 1
    // distance = count(x in [l,r] : p[i] < p[x] <= p[j]) (if p[i] < p[j])
    //           + count(x in [l,r] : p[j] < p[x] <= p[i]) (if p[j] < p[i])
    // Wait, distance = |rank(p[j]) - rank(p[i])| = number of values strictly between p[i] and p[j] in [l,r] + 1.
    //
    // Actually, rank(p[j]) - rank(p[i]) = number of elements in [l,r] with value in (p[i], p[j]]
    // (if p[i] < p[j]). So distance = count.
    // To maximize: choose [l,r] to maximize count of values in (p[i], p[j]).
    // But [l,r] must include positions i and j.
    // So l <= min(i,j), r >= max(i,j).
    // Max count = total count of values in (p[i], p[j]) among ALL positions.
    // Because we can choose l=0, r=n-1.
    // But wait, the new positions also depend on l and r.
    // If we choose l=0, r=n-1: new_pos(i) = rank(p[i]), new_pos(j) = rank(p[j]).
    // distance = |rank(p[j]) - rank(p[i])|.
    // This is just the number of values between p[i] and p[j] in the whole array.
    //
    // But we can also choose l < min(i,j) or r > max(i,j) to get a different l,
    // which shifts both positions by the same amount. So the distance doesn't change.
    //
    // Wait, that's not right. If l is different, the count of values in [l,r] changes.
    // Let me reconsider.
    //
    // For pair (i,j) with p[i] < p[j]:
    // After sorting [l,r] where l <= i, r >= j (or l <= j, r >= i):
    // new_pos(i) = l + count(x in [l,r] : p[x] <= p[i]) - 1
    // new_pos(j) = l + count(x in [l,r] : p[x] <= p[j]) - 1
    // distance = count(x in [l,r] : p[i] < p[x] <= p[j])
    // = count(x in [l,r] : p[i] < p[x]) - count(x in [l,r] : p[x] > p[j])
    // Wait, simpler: distance = count(x in [l,r] : p[i] < p[x] <= p[j])
    // = count of values in (p[i], p[j]] that are in positions [l,r].
    // To maximize: include ALL positions with values in (p[i], p[j]).
    // So choose l = min position of such a value or i or j, whichever is smallest.
    // r = max position of such a value or i or j, whichever is largest.
    // Then distance = count of values in (p[i], p[j]] in the whole array + 1 (for p[j] itself).
    // Wait, p[j] is at position j and has value p[j]. p[i] is at position i with value p[i].
    // After sorting, p[j] is at rank = count(x in [l,r] : p[x] <= p[j]).
    // p[i] is at rank = count(x in [l,r] : p[x] <= p[i]).
    // distance = rank(p[j]) - rank(p[i]) = count(x in [l,r] : p[i] < p[x] <= p[j]).
    // This includes position j itself (since p[j] <= p[j]).
    // So distance = 1 + count(x in [l,r], x != j : p[i] < p[x] < p[j]).
    // To maximize: include all positions with values in (p[i], p[j]).
    // Max distance = 1 + count of positions with values strictly between p[i] and p[j].
    // This is independent of l,r as long as [l,r] includes i,j and all those positions.
    //
    // Hmm, but we also need to consider the case where i or j is NOT in [l,r].
    // If i is not in [l,r] but j is: new_pos(j) = l + rank(p[j]) - 1.
    // But i's position doesn't change. So distance = |i - new_pos(j)|.
    // We can choose l to maximize this.
    //
    // This is getting complex. Let me just do O(n^3) for n=3000.
    // Actually O(n^3) might be too slow. Let me think...
    //
    // For n=3000, O(n^3) = 27e9, way too slow.
    // O(n^2 log n) or O(n^2) is needed.
    //
    // Key insight: for pair (i,j), the max distance is achieved by:
    // 1. Both in [l,r]: distance = count of values between p[i] and p[j] in [l,r].
    //    Max = count of values between p[i] and p[j] in whole array.
    // 2. Only one in [l,r]: the one in [l,r] can be pushed to the far end.
    //    Max distance for j in [l,r], i not: |i - l| or |i - r|, whichever is larger.
    //    Choose [l,r] to push j to the far end from i.
    //
    // For case 2: if j is in [l,r] and i is not:
    // If i < l: distance = l + rank(p[j] in [l,r]) - 1 - i
    //   To maximize: choose l as small as possible (l = 0) and r to maximize rank.
    //   rank(p[j] in [0,r]) = count(x in [0,r] : p[x] <= p[j]).
    //   Max when r = n-1: rank = rank of p[j] in whole array.
    //   distance = rank(p[j]) - i.
    //   But we need i < l = 0, which is impossible (i >= 0).
    // If i > r: distance = i - (l + rank(p[j] in [l,r]) - 1)
    //   To maximize: choose r as large as possible (r = n-1, but i > r means i = n, impossible).
    //
    // Hmm, case 2 doesn't seem to help much. Let me focus on case 1.
    //
    // For case 1 (both in [l,r]):
    // distance = count of values in (p[i], p[j]) in [l,r] + 1.
    // Max = count of values in (p[i], p[j]) in whole array + 1.
    // But we need [l,r] to include positions i and j.
    // So l <= min(i,j), r >= max(i,j).
    // The count includes all positions with values in (p[i], p[j]).
    // Some of these positions might be outside [min(i,j), max(i,j)].
    // If we choose l = 0, r = n-1: we include everything. Max distance achieved.
    //
    // Wait, but the distance formula assumes both i and j are in [l,r].
    // If l = 0, r = n-1: both are in [l,r].
    // distance = count(x : p[i] < p[x] <= p[j]) = rank(p[j]) - rank(p[i]).
    // This is the rank difference in the whole sorted array.
    //
    // But can we do better by choosing a smaller [l,r]?
    // No! Because including more elements can only increase or maintain the count.
    // So the max distance for pair (i,j) when both are in [l,r] is:
    // rank(p[j]) - rank(p[i]) (if p[i] < p[j]).
    //
    // But wait, what if we choose [l,r] such that some values between p[i] and p[j]
    // are NOT included? Then the count decreases, which is worse.
    // So the max is indeed the rank difference.
    //
    // Hmm, but the sample says d(4,5) = 4 for the first example.
    // p = [5,2,4,1,3] (0-indexed: p[0]=5, p[1]=2, p[2]=4, p[3]=1, p[4]=3)
    // Pair (3,4): p[3]=1, p[4]=3. Rank of 1 = 1, rank of 3 = 3. Distance = 3-1 = 2.
    // But the sample says d(4,5) = 4 (1-indexed positions 4,5 = 0-indexed 3,4).
    // The sample says: sort [1,4] (1-indexed) = [0,3] (0-indexed).
    // Original: [5,2,4,1,3]. After sorting [0,3]: [1,2,4,5,3].
    // Positions of 1 and 3: position 0 and 4. Distance = 4.
    // So the distance is NOT the rank difference. It's the position difference after sorting.
    //
    // Let me reconsider. After sorting [l,r]:
    // new_pos(i) = l + count(x in [l,r] : p[x] <= p[i]) - 1 (if p[i] is in [l,r])
    // For pair (3,4) with p[3]=1, p[4]=3:
    // Sort [0,3]: new_pos(3) = 0 + count(x in [0,3] : p[x] <= 1) - 1 = 0 + 1 - 1 = 0.
    //   new_pos(4) = 4 (not in [0,3], unchanged).
    //   distance = |0 - 4| = 4.
    //
    // So the key is that position 4 is NOT in the sorted range, so it stays at 4.
    // Position 3 moves to 0. Distance = 4.
    //
    // So case 2 (only one in [l,r]) CAN give a large distance.
    // For pair (i,j) where j is not in [l,r] and i is in [l,r]:
    // new_pos(i) = l + rank(p[i] in [l,r]) - 1.
    // distance = |new_pos(i) - j| = |l + rank - 1 - j|.
    // To maximize: choose l and r to push new_pos(i) as far from j as possible.
    // If j > r: distance = j - (l + rank - 1). Maximize by minimizing l + rank.
    //   l = 0, rank = 1 (choose r so that p[i] is the smallest in [0,r]).
    //   distance = j - 0 = j. But we need i in [0,r] and j > r.
    //   Choose r = j - 1 (or max possible < j).
    // If j < l: distance = (l + rank - 1) - j. Maximize by maximizing l + rank.
    //   l = r = n-1, rank = number of elements in [n-1,n-1] with value <= p[i] = 1.
    //   distance = n-1 + 1 - 1 - j = n - 1 - j.
    //   But we need j < l = n-1, so j <= n-2.
    //
    // For the general case: for pair (i,j), the max distance is:
    // max of:
    // - rank difference (both in [0,n-1]): |rank(p[j]) - rank(p[i])|
    // - j (push i to position 0, j not sorted): if i can be pushed to 0
    // - n-1-j (push i to position n-1, j not sorted): if i can be pushed to n-1
    // - i (push j to position 0, i not sorted): if j can be pushed to 0
    // - n-1-i (push j to position n-1, i not sorted): if j can be pushed to n-1
    //
    // Actually, the max distance for pair (i,j) is:
    // max(|rank(p[j]) - rank(p[i])|, j, n-1-j, i, n-1-i)
    // where rank is in the whole sorted array.
    //
    // Wait, that's not right either. Let me think more carefully.
    //
    // For pair (i,j) with i < j (0-indexed):
    // Option A: sort [0, j-1] (includes i, not j).
    //   new_pos(i) = count(x in [0,j-1] : p[x] <= p[i]) - 1.
    //   This is rank of p[i] among values at positions 0..j-1.
    //   distance = j - new_pos(i).
    //   Max when new_pos(i) is minimized: new_pos(i) = 0 (p[i] is smallest in [0,j-1]).
    //   distance = j.
    //   But p[i] might not be the smallest. We need to check.
    //   Actually, we can choose [l, j-1] where l <= i.
    //   new_pos(i) = l + count(x in [l,j-1] : p[x] <= p[i]) - 1.
    //   To minimize: l = 0 and count = 1 (p[i] is the only one <= p[i] in [0,j-1]).
    //   This requires p[i] < p[x] for all x in [0,j-1], x != i.
    //
    // Option B: sort [i+1, n-1] (includes j, not i).
    //   new_pos(j) = i+1 + count(x in [i+1,n-1] : p[x] <= p[j]) - 1.
    //   distance = new_pos(j) - i.
    //   Max when new_pos(j) is maximized: new_pos(j) = n-1.
    //   distance = n-1-i.
    //   Requires p[j] >= p[x] for all x in [i+1,n-1].
    //
    // OK this is getting very complex. Let me just implement O(n^3) for n<=500
    // and O(n^2) for larger n with a formula.
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int best = j - i; // no sorting
            // Try sorting [l, r] for all valid l, r
            // For n <= 3000, try all l, r is O(n^4) total. Too slow.
            // Instead, for each pair, compute the max distance directly.
            
            // Option 1: sort [0, j-1] (includes i, not j)
            {
                int cnt = 0;
                for (int x = 0; x < j; x++) if (p[x] <= p[i]) cnt++;
                int newPos = cnt - 1;
                best = max(best, j - newPos);
            }
            // Option 2: sort [i+1, n-1] (includes j, not i)
            {
                int cnt = 0;
                for (int x = i + 1; x < n; x++) if (p[x] <= p[j]) cnt++;
                int newPos = (i + 1) + cnt - 1;
                best = max(best, newPos - i);
            }
            // Option 3: sort [0, n-1] (both included)
            {
                int cnt_i = 0, cnt_j = 0;
                for (int x = 0; x < n; x++) {
                    if (p[x] <= p[i]) cnt_i++;
                    if (p[x] <= p[j]) cnt_j++;
                }
                best = max(best, abs((cnt_j - 1) - (cnt_i - 1)));
            }
            // Option 4: sort [l, r] where l <= i, r >= j, both included
            // distance = count(x in [l,r] : p[i] < p[x] <= p[j]) (if p[i] < p[j])
            // Max when [l,r] = [0,n-1]: count = cnt_j - cnt_i.
            // Already covered by option 3.
            
            // Option 5: sort [l, i] where l < i, j not included
            // This doesn't help because j stays at j and i moves within [l,i].
            // Max distance = j - l. But l >= 0, so max = j.
            // Already covered by option 1.
            
            // Option 6: sort [j, r] where r > j, i not included
            // Similar to option 2.
            
            ans += best;
        }
    }
    cout << ans << "\n";
    return 0;
}
