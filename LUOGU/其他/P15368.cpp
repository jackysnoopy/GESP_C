#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    while (Q--) {
        int imscor;
        long long k, x;
        cin >> k >> x;
        if (k == 1) {
            cout << (x == 1 ? "Yes" : "No") << "\n";
            continue;
        }
        // a_1=1, a_2=2, a_3=4, ...
        // Operation: pick u<v<w, a_w = a_u + a_v
        // Each u,v can only be used once total
        // We need a_k = x
        // For k=2: a_2=2, always. Can't change (no u<v<2 exists).
        // For k>=3: a_k starts at 2^(k-1). We can modify it.
        // Key insight: each unused pair (u,v) with u<v<k can contribute a_u+a_v once.
        // Max value of a_k = 2^(k-1) + sum of (a_u+a_v) for unused pairs
        // But we can also choose NOT to use a pair (it stays as original).
        // Actually: a_k = 2^(k-1) + sum of (a_u+a_v) for each operation applied
        // The target is x. We need x >= 2^(k-1) and (x - 2^(k-1)) can be expressed
        // as sum of distinct pairs (a_u + a_v) where u < v < k, each used at most once.
        // 
        // For k=3: pairs: (1,2). a_1+a_2=3. a_3 can be 4 or 4+3=7.
        // For k=4: pairs: (1,2),(1,3),(2,3). sums: 3,5,6. a_4 starts at 8.
        // 
        // Actually the constraint is stricter: u,v are chosen globally (not just < k).
        // Wait re-reading: "u和v在此前的所有操作中均未被作为'选出的u或v'使用过"
        // So u,v from ANY operation, not just those affecting a_k.
        // But we only care about making a_k = x. Other operations are irrelevant.
        // So for a_k, we apply operations with w=k, choosing unused u,v where u<v<k.
        // 
        // Wait no, the constraint is global: if we use u in ANY operation (any w),
        // it's consumed. But since we only care about a_k, we only need operations with w=k.
        // So we need to express (x - 2^(k-1)) as sum of some a_u + a_v values,
        // where each index in {1,...,k-1} appears in at most one pair.
        //
        // For k<=2: only x=2^(k-1) is possible.
        // For large k, the available sums grow exponentially, so most x values are reachable
        // as long as x >= 2^(k-1) and x <= max possible.
        //
        // Max possible = 2^(k-1) + sum of all a_u+a_v for u<v<k
        // = 2^(k-1) + (k-1)*2^(k-2) (each index appears in k-2 pairs? No...)
        // Actually sum of all a_u+a_v = sum_u a_u * (k-1-u) + sum_v a_v * (v-1)
        // This is complex. For difficulty 2, there's likely a simpler pattern.
        //
        // Let me think: a_i = 2^(i-1). Pairs (u,v): a_u + a_v = 2^(u-1) + 2^(v-1).
        // Since each is a power of 2, and u != v, a_u + a_v has exactly 2 bits set.
        // Using multiple pairs, we get a sum of values each with 2 bits set.
        // The deficit d = x - 2^(k-1) must be representable as sum of at most floor((k-1)/2) 
        // values, each being 2^a + 2^b with a < b < k-1, each bit used at most once.
        //
        // This is a subset-sum problem. For difficulty 2, maybe there's a greedy.
        // Actually, since we're using powers of 2, and each pair uses exactly 2 bits:
        // d must have even number of 1-bits (in binary), and each 1-bit must be at position < k-1.
        // AND we need d >= 0 and d <= max_sum.
        // AND d == 0 is OK (no operations).
        //
        // Wait, not exactly. We need to partition the set bits of d into pairs.
        // That requires even popcount. And all bits must be < k-1 (since u,v < k means a_u,a_v use bits 0..k-2).
        // Also d must be non-negative.
        // And we can't have more than floor((k-1)/2) pairs.
        //
        // For the answer to be Yes:
        // d >= 0, all bits of d are in positions 0..k-2, popcount(d) is even,
        // and popcount(d)/2 <= floor((k-1)/2) (which is always true if all bits < k-1).
        //
        // Also d can be 0 (no operations needed).
        // Actually we also need to handle the case where x < 2^(k-1): can't decrease.
        
        if (x < (1LL << (k - 1))) {
            cout << "No\n";
            continue;
        }
        if (k == 2) {
            cout << (x == 2 ? "Yes" : "No") << "\n";
            continue;
        }
        long long d = x - (1LL << (k - 1));
        if (d == 0) { cout << "Yes\n"; continue; }
        // Check: all bits of d in positions 0..k-2, and popcount even
        if (d >= (1LL << (k - 1))) { cout << "No\n"; continue; }
        int pc = 0;
        long long tmp = d;
        while (tmp) { pc += tmp & 1; tmp >>= 1; }
        cout << (pc % 2 == 0 ? "Yes" : "No") << "\n";
    }
    return 0;
}
