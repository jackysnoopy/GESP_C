#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> x(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        sort(x.begin(), x.end());
        
        struct Constraint { int l, r, t; };
        vector<Constraint> cons(k);
        for (int i = 0; i < k; i++) cin >> cons[i].l >> cons[i].r >> cons[i].t;
        
        // Binary search on answer: can we remove at least X trees?
        // Equivalently, can we keep at most n-X trees?
        // Or: maximize trees removed = n - minimize trees kept
        
        // For each constraint [l, r] needs at least t trees
        // We want to maximize trees removed = n - trees kept
        // Trees kept must satisfy all constraints
        
        // Greedy: sort constraints by r, for each constraint, if not enough trees in [l,r], 
        // add trees from right to left
        
        // Sort constraints by right endpoint
        sort(cons.begin(), cons.end(), [](const Constraint& a, const Constraint& b) {
            return a.r < b.r;
        });
        
        // Use a set to track which trees are kept
        vector<bool> kept(n, false);
        
        for (auto& con : cons) {
            // Count trees in [l, r] that are kept
            int lIdx = (int)(lower_bound(x.begin(), x.end(), con.l) - x.begin());
            int rIdx = (int)(upper_bound(x.begin(), x.end(), con.r) - x.begin()) - 1;
            if (lIdx > rIdx) {
                // No trees in range. But problem guarantees initial state satisfies constraints.
                // This shouldn't happen if we process greedily.
                continue;
            }
            int count = 0;
            for (int i = lIdx; i <= rIdx; i++) if (kept[i]) count++;
            
            // Need to keep more trees
            for (int i = rIdx; i >= lIdx && count < con.t; i--) {
                if (!kept[i]) {
                    kept[i] = true;
                    count++;
                }
            }
        }
        
        int keepCount = 0;
        for (int i = 0; i < n; i++) if (kept[i]) keepCount++;
        cout << (n - keepCount) << "\n";
    }
    return 0;
}
