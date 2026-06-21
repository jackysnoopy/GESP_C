#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) cin >> l[i];
        for (int i = 0; i < n; i++) cin >> r[i];
        long long totalNeeded = (long long)n * (n - 1) / 2;
        long long totalMin = 0, totalMax = 0;
        for (int i = 0; i < n; i++) { totalMin += l[i]; totalMax += r[i]; }
        if (totalMin > totalNeeded || totalMax < totalNeeded) {
            cout << "NO\n"; continue;
        }
        // Construct valid outdegree sequence
        // Sort by l ascending, assign l first, then distribute extra
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int a, int b) { return l[a] < l[b]; });
        vector<int> d(n);
        for (int i = 0; i < n; i++) d[i] = l[idx[i]];
        long long extra = totalNeeded - totalMin;
        // Distribute extra greedily: increase smaller outdegrees first
        // to satisfy score sequence condition
        for (int i = 0; i < n && extra > 0; i++) {
            long long canAdd = r[idx[i]] - d[i];
            long long add = min(extra, canAdd);
            d[i] += add;
            extra -= add;
        }
        if (extra > 0) { cout << "NO\n"; continue; }
        // Check score sequence condition
        sort(d.begin(), d.end());
        bool ok = true;
        long long sum = 0;
        for (int k = 1; k <= n; k++) {
            sum += d[k - 1];
            if (sum < (long long)k * (k - 1) / 2) { ok = false; break; }
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
