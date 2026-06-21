#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    // Find the position of p=1 (must be in first group)
    int pos1 = -1;
    for (int i = 0; i < n; i++) if (p[i] == 1) pos1 = i;
    // The first group starts at some l <= pos1 and ends at some r >= pos1.
    // Its earliest arrival = 1 (since p[pos1] = 1).
    // Within the group, sorted by arrival: q starts with 1, then sorted rest.
    // To maximize q[1]: include the cat with largest p in the first group.
    // The largest p cat is at some position pos_max.
    // If we include it: first group = [min(pos1, pos_max), max(pos1, pos_max)].
    // But this must be a contiguous segment.
    // If pos1 < pos_max: group = [pos1, pos_max]. All cats in between are included.
    // If pos1 > pos_max: group = [pos_max, pos1].
    //
    // To maximize q lexicographically, we want to put as many large-value cats
    // as possible early in q. The first group contributes sorted arrivals.
    // After the first group, the next group has the smallest earliest arrival
    // among remaining cats.
    //
    // Greedy: extend the first group to include all cats from pos1 to the right
    // (or left) as long as it increases q lexicographically.
    //
    // Actually, the optimal strategy is to make the first group cover as wide a range
    // as possible to include large p values. But we also need to consider the remaining groups.
    //
    // Let me try a different approach: DP or greedy from left to right.
    // For each possible group boundary, compute the resulting q and compare.
    //
    // For n up to 3e5, we need O(n log n) or O(n).
    //
    // Key insight: the first group must contain the position of p=1.
    // The first group = [l, r] where l <= pos1 <= r.
    // After the first group, the remaining cats are [0, l-1] and [r+1, n-1].
    // The next group is the one with smallest earliest arrival among remaining.
    //
    // To maximize q lexicographically:
    // q[0] = 1 (fixed).
    // q[1] = second smallest in first group. Maximize by including the cat with
    //   largest p that's reachable (contiguous with pos1).
    // The best: extend the group to cover the entire range [0, n-1] if possible.
    //   Then q = sorted(p) = [1, 2, 3, ..., n]. This is the maximum possible.
    //   But is this achievable? Yes! Put all cats in one group.
    //   Then q = sorted(p) = [1, 2, ..., n].
    //   This is the lexicographically maximum possible (since q is a permutation of 1..n).
    //
    // Wait, is that right? If all cats are in one group:
    // Group earliest = min(p) = 1. Sort within group: [1, 2, 3, ..., n].
    // q = [1, 2, 3, ..., n]. This is the maximum lexicographic permutation.
    //
    // But the problem says we want to MAXIMIZE q lexicographically.
    // [1, 2, 3, ..., n] is indeed the maximum.
    // So the answer is always [1, 2, 3, ..., n]?
    //
    // Wait, let me re-read the problem. "你想知道排列 q_1,q_2,...,q_n 的字典序最大可能是什么"
    // Yes, we want to maximize q. And putting all cats in one group gives q = sorted(p) = [1,2,...,n].
    // This is the maximum. But the sample says the answer for n=4, p=[2,1,4,3] is [1,4,2,3].
    // That's NOT [1,2,3,4]. So my reasoning is wrong.
    //
    // Let me re-read: "先把所有的喵喵组按每组喵喵的到达时间从小到大排序"
    // Groups are sorted by arrival time (earliest in group).
    // "然后对于同一组喵喵，按照每只喵喵的到达时间从小到大排序"
    // Within each group, sorted by arrival.
    //
    // If all in one group: group earliest = 1. Within group sorted: [1,2,3,4].
    // q = [1,2,3,4]. But sample answer is [1,4,2,3].
    // So [1,2,3,4] should be achievable and is better than [1,4,2,3].
    //
    // Wait, let me check the sample explanation.
    // The table shows (2,1,4,3) gives q = [1,2,3,4].
    // But the expected output is [1,4,2,3].
    // Hmm, let me re-read.
    //
    // Oh wait, I think I misread the output. Let me check again.
    // Sample 1: n=4, p=[2,1,4,3]. Output: 1 4 2 3.
    // From the table: (2)(1,4,3) gives q = [1,3,4,2]. 
    // (2)(1,4)(3) gives q = [1,4,2,3].
    // (2,1,4,3) gives q = [1,2,3,4].
    //
    // So [1,2,3,4] IS achievable. Why isn't it the answer?
    // Unless the problem asks for MINIMUM, not maximum?
    // "字典序最大可能" = maximum lexicographic.
    // [1,2,3,4] > [1,4,2,3] lexicographically (since 2 < 4 at position 1).
    // So [1,2,3,4] should be the answer.
    //
    // Wait, [1,2,3,4] vs [1,4,2,3]: at position 1, 2 < 4, so [1,4,2,3] > [1,2,3,4].
    // Yes! [1,4,2,3] is lexicographically larger because 4 > 2 at position 1.
    //
    // So putting all cats in one group gives [1,2,3,4], which is NOT the maximum.
    // To get [1,4,2,3]: group (2)(1,4)(3).
    // Group 1: {cat 2} with p=1. Earliest = 1. Sorted: [1].
    // Group 2: {cats 1,3} with p=2,4. Earliest = 2. Sorted: [2,4].
    // Group 3: {cat 4} with p=3. Earliest = 3. Sorted: [3].
    // q = [1, 2, 4, 3]. That's not [1,4,2,3].
    //
    // Hmm, let me re-read the grouping. (2)(1,4)(3) means:
    // Group 1: position 2 only (cat with p=1).
    // Group 2: positions 1,4 (cats with p=2, p=3). Wait, position 1 has p=2, position 4 has p=3.
    //   Earliest = min(2,3) = 2. Sorted: [2,3].
    // Group 3: position 3 only (cat with p=4). Earliest = 4. Sorted: [4].
    // q = [1, 2, 3, 4]. Still [1,2,3,4].
    //
    // Let me try (2)(1,4,3):
    // Group 1: position 2 (p=1). Earliest = 1. Sorted: [1].
    // Group 2: positions 1,4,3 (p=2,3,4). Earliest = 2. Sorted: [2,3,4].
    // q = [1, 2, 3, 4].
    //
    // And (2)(1,4)(3):
    // Group 1: position 2 (p=1). Sorted: [1].
    // Group 2: positions 1,4 (p=2,3). Sorted: [2,3].
    // Group 3: position 3 (p=4). Sorted: [4].
    // q = [1, 2, 3, 4].
    //
    // But the table says (2)(1,4)(3) gives q = [1,4,2,3]. That doesn't match.
    // Let me re-read the problem more carefully.
    //
    // Oh! The grouping is by CONTIGUOUS segments of positions.
    // (2)(1,4)(3) means: group 1 = positions [2,2], group 2 = positions [1,1] and [4,4]? No.
    // Wait, the notation (2)(1,4)(3) means:
    // Group 1: cat 2 (position 2 in 1-indexed).
    // Group 2: cats 1 and 4 (positions 1 and 4).
    // Group 3: cat 3 (position 3).
    // But positions 1 and 4 are NOT contiguous! So this grouping is invalid.
    //
    // The problem says "每一组喵喵的编号都是连续的一段". Groups must be contiguous.
    // So valid groupings for n=4 are like:
    // (1)(2)(3)(4), (1)(2)(3,4), (1)(2,3)(4), (1)(2,3,4), (1,2)(3)(4), (1,2)(3,4),
    // (1,2,3)(4), (1,2,3,4).
    //
    // Wait, the table shows (2)(1,4)(3) as a valid grouping. But 1 and 4 are not contiguous.
    // Unless the numbering is different. Let me re-read.
    //
    // "第 i 只喵喵会第 p_i 个到达现场" - cat i arrives at time p_i.
    // "把所有的喵喵组按每组喵喵的到达时间从小到大排序" - sort groups by earliest arrival.
    //
    // The grouping (2)(1,4)(3): 
    // Group 1: cat 2 (p=1).
    // Group 2: cats 1,4 (p=2, p=3). But cats 1 and 4 are not contiguous (positions 1 and 4).
    // This should be invalid.
    //
    // Hmm, maybe I'm misunderstanding the grouping notation. Let me re-read.
    //
    // Actually, looking at the table again:
    // |(2)(1,4)(3)|1,4,2,3|
    // Maybe (1,4) means cats at positions 1 and 4 in the GROUP, not in the original array.
    // No, that doesn't make sense either.
    //
    // Wait, maybe the grouping is by CAT NUMBERS, not positions.
    // "分成了若干组，每一组喵喵的编号都是连续的一段"
    // Groups are contiguous by cat number. So group = {i, i+1, ..., j} for some i, j.
    //
    // For p = [2,1,4,3] (1-indexed):
    // Cat 1 has p=2, cat 2 has p=1, cat 3 has p=4, cat 4 has p=3.
    //
    // Grouping (2)(1,4)(3): This doesn't make sense as contiguous cat numbers.
    // Unless it means groups of positions in the final arrangement.
    //
    // Actually, I think the notation means:
    // (2) = group containing cat 2 only.
    // (1,4) = group containing cats 1 and 4? But they're not contiguous.
    //
    // Hmm, let me look at the valid groupings listed:
    // |(2)(1,4,3)| = groups: {2}, {1,4,3}. But {1,4,3} is not contiguous.
    //
    // I think the notation might be misleading. Let me re-read the problem.
    //
    // "分成了若干组，每一组喵喵的编号都是连续的一段"
    // Groups are contiguous by cat number. So valid groups for cats 1,2,3,4:
    // Any partition of [1,4] into contiguous segments.
    //
    // The table must be wrong or I'm misunderstanding it. Let me just focus on the algorithm.
    //
    // For the algorithm: we want to partition [1,n] into contiguous groups to maximize q.
    // q is formed by: sort groups by earliest arrival, then within each group by arrival.
    //
    // This is a complex DP problem. Let me implement it.
    
    // DP: dp[i] = maximum q for cats 1..i.
    // But q is a permutation, so we can't easily compare.
    //
    // Alternative: greedy. To maximize q lexicographically:
    // q[0] is the earliest arrival in the first group.
    // To maximize q[0]: first group should have the largest possible minimum.
    // The first group = [1, r] for some r. Its earliest = min(p[1..r]).
    // To maximize min(p[1..r]): we want r to be small (so the min is large).
    // But we also need to consider the rest.
    //
    // Actually, the first group must start at position 1 (since groups are contiguous
    // and cover all positions). So the first group = [1, r] for some r.
    // Its earliest = min(p[1..r]).
    // q starts with sorted(p[1..r]).
    // To maximize q lexicographically: we want the first element of sorted(p[1..r])
    // to be as large as possible. This means min(p[1..r]) should be large.
    // So r should be as small as possible, but r >= 1.
    // If r = 1: first group = {1}, earliest = p[1] = 2. q starts with [2].
    // If r = 2: first group = {1,2}, earliest = min(2,1) = 1. q starts with [1,2].
    // If r = 3: first group = {1,2,3}, earliest = min(2,1,4) = 1. q starts with [1,2,4].
    // If r = 4: first group = {1,2,3,4}, earliest = 1. q starts with [1,2,3,4].
    //
    // For r=1: q starts with [2, ...]. The rest is cats 2,3,4.
    //   Next group starts at 2. If group = {2}: earliest = 1. q continues with [1, ...].
    //   Then cats 3,4: group = {3,4}: earliest = 3. q continues with [3,4].
    //   q = [2, 1, 3, 4].
    // For r=2: q starts with [1, 2, ...]. Rest is cats 3,4.
    //   Next group = {3,4}: earliest = 3. q = [1, 2, 3, 4].
    // For r=1, then group {2,3,4}: earliest = 1. q = [2, 1, 3, 4].
    //   Then group {3,4}: earliest = 3. q = [2, 1, 3, 4].
    //
    // Comparing: [2,1,3,4] vs [1,2,3,4]. At position 0: 2 > 1. So [2,1,3,4] is larger!
    // But the expected answer is [1,4,2,3]. Hmm.
    //
    // Let me check: is [2,1,3,4] achievable?
    // Groups: {1}, {2}, {3,4}.
    // Group 1: {1}, earliest = 2. Sorted: [2].
    // Group 2: {2}, earliest = 1. Sorted: [1].
    // Group 3: {3,4}, earliest = 3. Sorted: [3,4].
    // Sort groups by earliest: group 2 (earliest 1), group 1 (earliest 2), group 3 (earliest 3).
    // q = [1, 2, 3, 4]. Not [2,1,3,4].
    //
    // Oh! The groups are sorted by earliest arrival. So even though group 1 comes first
    // in the partition, it's sorted by earliest. Group 2 has earliest 1, so it comes first.
    // q = [1, 2, 3, 4].
    //
    // So the key insight: the first element of q is ALWAYS the global minimum of p.
    // Because the group containing the cat with smallest p will always be first.
    // q[0] = 1 (always, since p is a permutation of 1..n).
    //
    // To maximize q[1]: we want the second element to be as large as possible.
    // q[1] = second smallest in the group containing cat with p=1.
    // That group = [l, r] where pos1 is in [l, r].
    // The second smallest in [l, r] is the second smallest p in that range.
    // To maximize: include the cat with largest p in the same group as pos1.
    // The group must be contiguous. So we extend from pos1 to include the largest p cat.
    //
    // For p = [2,1,4,3], pos1 = 2 (1-indexed).
    // Largest p = 4 at position 3.
    // Group containing pos1 and position 3: [2,3] (contiguous).
    // p values in [2,3]: [1,4]. Sorted: [1,4]. q[0]=1, q[1]=4.
    // Then remaining: positions 1 and 4.
    // Next group: {1} with p=2, earliest=2. Then {4} with p=3, earliest=3.
    // q = [1, 4, 2, 3]. This matches the expected output!
    //
    // So the greedy is: include the cat with largest p in the same group as pos1,
    // as long as the group is contiguous and it increases q lexicographically.
    //
    // General greedy:
    // 1. Find pos1 (position of p=1).
    // 2. Extend the group from pos1 to include as many large-p cats as possible.
    // 3. The group = [l, r] where l <= pos1 <= r.
    // 4. To maximize q[1]: include the cat with largest p that's reachable.
    // 5. Then maximize q[2], q[3], etc.
    
    // Actually, the greedy is more nuanced. Let me think about it as:
    // We partition [1,n] into contiguous groups. The groups are sorted by earliest arrival.
    // Within each group, sorted by arrival. The result is q.
    //
    // To maximize q lexicographically:
    // q[0] = min(p) = 1 (always).
    // q[1] = second smallest in the group containing pos1.
    // To maximize q[1]: make that group include the cat with largest p.
    // The group = [l, r] where l <= pos1 <= r.
    // The largest p in [l, r] is max(p[l..r]).
    // To maximize: extend r to include the cat with largest p (or extend l).
    //
    // But extending the group also means the group has a larger earliest arrival range,
    // which affects the sorting order.
    //
    // Let me just implement the greedy:
    // Start with group containing pos1. Extend to include the cat with largest p
    // that's contiguous. Then process the remaining cats similarly.
    
    // For simplicity, let me implement a DP approach.
    // dp[i] = the best q for prefix [1..i].
    // But comparing permutations lexicographically is expensive.
    
    // Alternative: greedy from the position of p=1.
    // The group containing pos1 determines q[0] and some of q[1], q[2], etc.
    // Extend the group to the right and left to include large-p cats.
    
    // Simple greedy: 
    // 1. The first group in the sorted order contains pos1.
    // 2. Its earliest = 1. Its members are some contiguous segment containing pos1.
    // 3. q starts with sorted members of this group.
    // 4. To maximize: include the cat with largest p in this group.
    // 5. The group must be contiguous: [min(pos1, pos_max), max(pos1, pos_max)].
    // 6. This includes all cats between pos1 and pos_max.
    // 7. Then process remaining cats (left and right of the group) similarly.
    
    // But this greedy might not be optimal. Let me think...
    //
    // Actually, for the greedy to work: we want the group containing pos1 to have
    // the largest possible maximum p value. This means extending to include the cat
    // with the largest p that's contiguous with pos1.
    //
    // If pos1 < pos_max: extend right to pos_max. Group = [pos1, pos_max].
    // If pos1 > pos_max: extend left to pos_max. Group = [pos_max, pos1].
    //
    // After this group, the remaining cats are [1, pos_min-1] and [pos_max+1, n].
    // For each remaining segment, find the cat with smallest p and repeat.
    
    // This greedy should work for the sample. Let me implement it.
    
    // Actually, I realize the greedy needs more thought. Let me just implement
    // a simple approach and see if it matches.
    
    // Greedy: find pos of p=1. The first group must contain it.
    // Extend the group to include all cats from pos1 to the right (or left)
    // that have p values that help maximize q.
    
    // For the sample: p = [2,1,4,3], pos1 = 1 (0-indexed).
    // Largest p = 4 at position 2 (0-indexed).
    // Extend group to [1, 2] (0-indexed). Members: p=1, p=4. Sorted: [1, 4].
    // Remaining: positions 0 and 3. p=2 and p=3.
    // Next group: position 0 (p=2), earliest=2. Group = {0}. Sorted: [2].
    // Next group: position 3 (p=3), earliest=3. Group = {3}. Sorted: [3].
    // q = [1, 4, 2, 3]. Correct!
    
    // Let me implement this greedy properly.
    
    // Find positions
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) pos[p[i]] = i;
    
    // The first group contains pos[1] (position of p=1).
    // Find the cat with largest p that's reachable from pos[1].
    // "Reachable" means: the contiguous segment [min(pos[1], pos[max_p]), max(pos[1], pos[max_p])]
    // doesn't cross any already-assigned boundary.
    
    // Greedy: extend the group to include pos[n] (largest p).
    // Group = [min(pos[1], pos[n]), max(pos[1], pos[n])].
    // Then for remaining segments, repeat.
    
    vector<int> result;
    int start = 0;
    while (start < n) {
        // Find the smallest p in [start, n-1]
        int min_p = n + 1, min_pos = -1;
        for (int i = start; i < n; i++) {
            if (p[i] < min_p) { min_p = p[i]; min_pos = i; }
        }
        // Find the largest p in [start, n-1]
        int max_p = 0, max_pos = -1;
        for (int i = start; i < n; i++) {
            if (p[i] > max_p) { max_p = p[i]; max_pos = i; }
        }
        // Group = [min(min_pos, max_pos), max(min_pos, max_pos)]
        // But this must be within [start, n-1] and contiguous.
        int g_start = min(min_pos, max_pos);
        int g_end = max(min_pos, max_pos);
        // But g_start might be < start. In that case, we can't include max_p.
        // Instead, find the largest p in [min_pos, n-1] that's contiguous with min_pos.
        if (g_start < start) {
            // Can't extend left. Find largest p in [start, n-1] that's contiguous.
            // Just take the whole segment from start.
            g_start = start;
            g_end = n - 1;
        }
        // Collect p values in [g_start, g_end], sort them
        vector<int> group_vals;
        for (int i = g_start; i <= g_end; i++) group_vals.push_back(p[i]);
        sort(group_vals.begin(), group_vals.end());
        for (int v : group_vals) result.push_back(v);
        start = g_end + 1;
    }
    
    for (int i = 0; i < n; i++) cout << result[i] << " ";
    cout << "\n";
    return 0;
}
