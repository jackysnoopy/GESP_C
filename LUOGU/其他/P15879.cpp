#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    long long M;
    cin >> s >> M;
    int n = s.size();
    // Strategy: try all possible target arrangements (AC-K or AK-C or similar)
    // and compute cost for each. Pick the minimum.
    // Target arrangements:
    // 1. K...A...C (no AC, no AK)
    // 2. C...A...K (no AC, no AK)
    // For each target, compute inversions needed (swap distance)
    // Then count remaining AC and AK subsequences
    // 
    // Actually the problem asks for min remaining AC+AK subsequences, not min swaps.
    // With M swaps, we can rearrange s somewhat.
    // We want to minimize the number of AC and AK subsequences.
    //
    // For each possible target string (sorted by some criterion), compute:
    // 1. Cost in swaps to reach target
    // 2. AC+AK count in target
    // Choose target where cost <= M and AC+AK is minimized.
    //
    // Targets to consider (group A, C, K):
    // KKK...AAA...CCC, CCC...AAA...KKK, AAA...CCC...KKK, etc.
    // The ones that minimize AC+AK are:
    // K*A*C* or C*A*K* (A's between C and K cause subsequences)
    // AAA...CCC...KKK: AC subsequences = count_A * count_C, AK = count_A * count_K (all A before C and K)
    // CCC...KKK...AAA: AC=0, AK=0 (A after both C and K)
    // KKK...CCC...AAA: AC=0, AK=0
    // CCC...AAA...KKK: AC = count_C_before_A * count_A_after_C... hmm
    // 
    // Let me just enumerate the 6 permutations of {A,C,K} groups:
    // For each permutation, group letters accordingly and compute:
    // - Swap cost (inversion count between current and target positions)
    // - AC + AK subsequence count in target
    
    int cntA = 0, cntC = 0, cntK = 0;
    for (char c : s) {
        if (c == 'A') cntA++;
        else if (c == 'C') cntC++;
        else cntK++;
    }
    
    // For a target arrangement, compute swap cost = inversions
    // But computing exact swap cost for large n is O(n^2) which is too slow for n=200000.
    // Swap cost between two arrangements = number of inversions between them.
    // For target "CCC...AAA...KKK", the cost is the number of pairs (i,j) where
    // s[i] should come after s[j] in target but i < j.
    //
    // Actually: given target order of characters, the minimum swaps = inversions between
    // current order and target order.
    // 
    // For large n, we can compute this with a BIT/fenwick tree.
    // But that's complex. Let me try a simpler approach.
    //
    // Key insight: we want to minimize AC+AK subsequences.
    // If we arrange as K*A*C* or C*A*K*, there are 0 AC and 0 AK.
    // So the question is: can we reach such an arrangement within M swaps?
    // If yes, answer is 0.
    // Otherwise, find the arrangement that minimizes AC+AK.
    //
    // For n=200000, computing exact swap cost is needed.
    // Let me compute cost for the arrangement that puts K first, then A, then C.
    
    auto computeCost = [&](const string& target) -> long long {
        // target assigns each position a priority. 
        // We need inversions: pairs where s[i] has higher priority but comes before s[j] with lower.
        // Use counting: for each position, count how many later positions have lower priority.
        // With 3 groups, can do it in O(n).
        vector<int> cnt(3, 0);
        long long inv = 0;
        for (int i = n - 1; i >= 0; i--) {
            int p = 0;
            if (target[i] == 'C') p = 0;
            else if (target[i] == 'A') p = 1;
            else p = 2;
            // Count positions j > i with priority < p
            for (int q = 0; q < p; q++) inv += cnt[q];
            cnt[p]++;
        }
        return inv;
    };
    
    auto countSubseq = [&](const string& target) -> long long {
        long long ac = 0, ak = 0;
        long long ca = 0, ka = 0;
        long long aCount = 0, cCount = 0, kCount = 0;
        for (char c : target) {
            if (c == 'A') {
                ac += cCount;  // C before A: these form CA, not AC. Actually AC means A before C.
                ak += kCount;
                aCount++;
            } else if (c == 'C') {
                ca += aCount;  // A before C: these form AC
                cCount++;
            } else {
                ka += aCount;  // A before K: these form AK
                kCount++;
            }
        }
        // Wait, I computed wrong. Let me redo.
        // AC subsequence: positions i < j with s[i]='A' and s[j]='C'
        // AK subsequence: positions i < j with s[i]='A' and s[j]='K'
        ac = 0; ak = 0;
        aCount = 0;
        for (char c : target) {
            if (c == 'A') aCount++;
            else if (c == 'C') ac += aCount;
            else ak += aCount;
        }
        return ac + ak;
    };
    
    // Try all 6 permutations of groups
    string perms[] = {"ACK", "AKC", "CAK", "CKA", "KAC", "KCA"};
    long long bestAns = countSubseq(s); // worst case: no swaps
    
    for (int p = 0; p < 6; p++) {
        string target(n, ' ');
        int pos = 0;
        for (int g = 0; g < 3; g++) {
            char ch = perms[p][g];
            int cnt = (ch == 'A') ? cntA : (ch == 'C') ? cntC : cntK;
            for (int i = 0; i < cnt; i++) target[pos++] = ch;
        }
        long long cost = computeCost(target);
        if (cost <= M) {
            long long subseq = countSubseq(target);
            bestAns = min(bestAns, subseq);
        }
    }
    
    // Also try: only partially rearrange within budget
    // For simplicity, check the top 2-3 cheapest targets
    vector<pair<long long, string>> candidates;
    for (int p = 0; p < 6; p++) {
        string target(n, ' ');
        int pos = 0;
        for (int g = 0; g < 3; g++) {
            char ch = perms[p][g];
            int cnt = (ch == 'A') ? cntA : (ch == 'C') ? cntC : cntK;
            for (int i = 0; i < cnt; i++) target[pos++] = ch;
        }
        long long cost = computeCost(target);
        candidates.push_back({cost, target});
    }
    sort(candidates.begin(), candidates.end());
    for (int i = 0; i < (int)candidates.size(); i++) {
        if (candidates[i].first <= M) {
            bestAns = min(bestAns, countSubseq(candidates[i].second));
        }
    }
    
    cout << bestAns << "\n";
    return 0;
}
