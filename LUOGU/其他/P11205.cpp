#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        // Find current mex
        long long mex = 1;
        for (int i = 0; i < n; i++) {
            if (a[i] == mex) mex++;
            else if (a[i] > mex) break;
        }
        // Check if we can create a pile of size mex
        long long total_removable = 0;
        for (int i = 0; i < n; i++) total_removable += a[i] - 1;
        if (total_removable >= mex) {
            // We can create mex. New mex = mex + 1? Or higher?
            // After creating mex, the set has 1, 2, ..., mex.
            // But some original piles might have lost petals.
            // The new set = (original with some reductions) + {mex}.
            // New mex >= mex + 1.
            // Can we achieve mex + 1? We'd need mex + 1 in the set.
            // But we already used our one operation.
            // Unless mex + 1 was already in the original set.
            // Check: is mex + 1 in the original set?
            bool has_mex_plus_1 = false;
            for (int i = 0; i < n; i++) if (a[i] == mex + 1) has_mex_plus_1 = true;
            if (has_mex_plus_1) cout << mex + 2 << "\n";
            else cout << mex + 1 << "\n";
        } else {
            cout << mex << "\n";
        }
    }
    return 0;
}
