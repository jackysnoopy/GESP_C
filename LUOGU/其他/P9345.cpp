#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 夕阳西下几时回
// Find a permutation of 1..n with exactly k distinct gcd(a[i], a[i+1]) values.
// Multiple test cases. n up to 3e5, sum n up to 6e5.
//
// Key observations:
// - For k=1: use 1,2,3,...,n (consecutive). gcd(i,i+1)=1 for all i, gcd(n,1)=1. All 1s.
// - For k=n: impossible for n>=3 (can't have n distinct gcd values with n edges).
// - For general k: we need to construct a permutation where gcd(a[i],a[i+1])
//   takes exactly k distinct values.
//
// Strategy:
// - k=1: ascending order 1,2,...,n. All gcds = 1.
// - For k>1: use pairs of multiples to create non-1 gcds.
//   E.g., place (2,4) adjacently → gcd=2.
//   Place (3,6) adjacently → gcd=3.
//   Each such pair contributes 1 to the count of distinct gcds.
//   We need k-1 such pairs (plus the base gcd=1 for other edges).
//   Maximum pairs: floor(n/2). So k can be at most floor(n/2) + 1.
//   But actually we can also get gcd > 1 from longer chains.
//   
//   For the construction:
//   - Use 1,2,3,...,n as base (all gcd=1, k=1).
//   - To increase k: swap adjacent elements to create non-1 gcds.
//   - Place (2,4) together: gcd=2. (3,6): gcd=3. (4,8): gcd=4. etc.
//   - We need floor((n-1)/2) pairs at most.
//   - For k distinct values: use pairs (2,4), (3,6), ..., (k-1, 2*(k-1)).
//   - This works if 2*(k-1) <= n, i.e., k <= n/2 + 1.
//
// - k > n/2 + 1: impossible? Not necessarily. We can get gcd=1 from multiple edges.
//   Actually: the maximum number of distinct gcd values is bounded by... 
//   For a permutation of 1..n: the gcd of adjacent pairs can be 1, 2, 3, ..., floor(n/2).
//   Plus maybe some larger values. The maximum is related to the number of distinct
//   values we can achieve.
//   
//   Actually, for any permutation, gcd(a[i], a[i+1]) can be any value from 1 to floor(n/2)
//   (at most). The maximum number of distinct values is floor(n/2).
//   Wait, gcd(n, n-1) = 1. gcd(n, n-2) could be 2 if n is even.
//   For n=11 (sample): k=4 is achievable with gcd values 1, 2, 3, 5.
//   
//   Let me check: for n=6, k=5. Is it possible?
//   We need 5 distinct gcd values from 6 edges. 
//   Possible gcd values: 1, 2, 3 (since 4 needs both 4 and 8, but 8 > 6).
//   Actually 4 is possible if both 4 and 4 are adjacent... no, all values distinct.
//   gcd(4, 2) = 2, gcd(4, 6) = 2, gcd(4, 8) - 8 > 6.
//   gcd(5, 10) - 10 > 6. gcd(6, 3) = 3.
//   So for n=6: possible gcd values are 1, 2, 3. Max k = 3.
//   So for n=6, k=5 is impossible. Sample says "No". Correct!
//
// For n=7, k=1: ascending 1..7. gcd all = 1. Correct.
//
// For n=11, k=4: construct permutation with gcd values {1, 2, 3, 5}.
// Sample: 1 11 9 3 6 7 8 2 5 10 4
// gcds: gcd(1,11)=1, gcd(11,9)=1, gcd(9,3)=3, gcd(3,6)=3, gcd(6,7)=1,
//        gcd(7,8)=1, gcd(8,2)=2, gcd(2,5)=1, gcd(5,10)=5, gcd(10,4)=2, gcd(4,1)=1
// Distinct: {1, 2, 3, 5} = 4 values. Correct!

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    
    while (T--) {
        int n, k;
        cin >> n >> k;
        
        if (n <= 2) {
            if (k == 1) {
                cout << "Yes\n";
                for (int i = 1; i <= n; i++) cout << i << (i < n ? " " : "\n");
            } else {
                cout << "No\n";
            }
            continue;
        }
        
        if (k == 1) {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++) cout << i << (i < n ? " " : "\n");
            continue;
        }
        
        // For k >= 2: we need k-1 non-1 gcd values.
        // Each non-1 gcd requires a pair (a, b) where gcd(a,b) = g > 1.
        // We can create pairs (2,4), (3,6), (5,10), etc.
        // Maximum pairs: we need 2*(k-1) <= n for k-1 pairs of distinct multiples.
        // Plus 1 for the gcd=1 edges.
        // Actually we also need n - 2*(k-1) >= 1 for the remaining elements.
        // So 2*(k-1) + 1 <= n, i.e., k <= (n+1)/2.
        // 
        // But we can also create pairs sharing elements: (2,4) and (4,8) both use 4.
        // gcd(2,4)=2, gcd(4,8)=4. Two distinct gcds from 3 elements.
        // This way we can get more distinct gcds.
        //
        // The maximum k is floor(n/2) + 1 (using pairs 2-4, 3-6, ..., and gcd=1).
        // Wait: for n=11, floor(11/2)+1 = 6. But the sample achieves k=4.
        // Can we achieve k=5 for n=11? Need 5 distinct gcd values.
        // Pairs: (2,4)→2, (3,6)→3, (5,10)→5, (4,8)→4. That's 4 non-1 values + 1 = 5.
        // But 4 is used in both (2,4) and (4,8). We'd need a chain: 2,4,8.
        // That's 3 elements, 2 edges, 2 distinct gcds. 
        // Then (3,6)→3, (5,10)→5. Total 5 elements for 4 non-1 gcds.
        // Remaining 6 elements with gcd=1 edges. Total k=5.
        // But wait, (2,4,8) gives gcds 2 and 4. Then (3,6) gives 3. (5,10) gives 5.
        // Total non-1: {2,3,4,5} = 4. Plus 1 = 5. Works!
        //
        // Can we go higher? For n=11: (2,4,8)→{2,4}, (3,6)→{3}, (5,10)→{5}, 
        // (7,?)→7 needs 14 > 11. So max non-1 = 4, k=5.
        // But we could also use (6,9)→3 (already have 3). Or (8,10)→2 (already have 2).
        // Hmm, (2,6)→2, (3,9)→3. But 6 and 9 already used.
        // I think for n=11, max k = 5.
        //
        // For the problem: k <= (n-1)/2 + 1 seems to be the bound.
        // Actually: the maximum number of distinct gcd values for a permutation of 1..n
        // is the number of integers g in [2, n/2] such that there exist at least 2 
        // multiples of g in [1,n]. Plus 1 for gcd=1.
        // That's floor(n/2) - 1 + 1 = floor(n/2) for n >= 4.
        // Wait no: for g in [2, floor(n/2)], we need 2*g <= n, so g <= n/2.
        // Count = floor(n/2) - 1 (values 2, 3, ..., floor(n/2)).
        // Plus 1 = floor(n/2).
        // But we also need enough elements to form the pairs.
        // Each g needs at least 2 multiples. Elements used: at least 2 per g.
        // Total elements for non-1: at least 2*(k-1).
        // Plus elements for gcd=1: at least 1.
        // So 2*(k-1) + 1 <= n → k <= (n+1)/2.
        //
        // But with shared elements (chains), we can do better.
        // A chain of multiples: g, 2g, 4g, 8g, ... gives gcds g, 2g, 4g, ...
        // Uses L elements, gives L-1 distinct gcds.
        // So k-1 <= n-1 (use all elements in one chain). k <= n.
        // But the chain needs all elements to be distinct and in [1,n].
        // For g=2: chain 2,4,8,16,... uses floor(log2(n/g))+1 elements.
        //
        // This is getting complex. Let me just implement a simple construction
        // and check the bound.
        
        // Simple bound: k <= n/2 + 1 for n >= 3.
        // Construction: pairs (2,4), (3,6), ..., ((k-1), 2*(k-1))
        // Plus remaining elements with gcd=1.
        
        int maxPairs = (n - 1) / 2; // max non-1 gcd values
        if (k > maxPairs + 1 || k < 1) {
            cout << "No\n";
            continue;
        }
        
        // Construct permutation
        vector<bool> used(n + 1, false);
        vector<int> perm;
        
        if (k == 1) {
            for (int i = 1; i <= n; i++) perm.push_back(i);
        } else {
            // Place pairs to create non-1 gcds
            for (int g = 2; g < k + 1; g++) {
                if (2 * g <= n && !used[g] && !used[2 * g]) {
                    perm.push_back(g);
                    perm.push_back(2 * g);
                    used[g] = true;
                    used[2 * g] = true;
                }
            }
            // Fill remaining
            for (int i = 1; i <= n; i++) {
                if (!used[i]) perm.push_back(i);
            }
        }
        
        cout << "Yes\n";
        for (int i = 0; i < n; i++) {
            cout << perm[i] << (i + 1 < n ? " " : "\n");
        }
    }
    return 0;
}
