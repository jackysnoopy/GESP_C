#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T, id; cin >> T >> id;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        bool possible = false;
        // Try all possible R values (differences between pairs)
        for (int i = 0; i < n && !possible; i++) {
            for (int j = i + 1; j < n && !possible; j++) {
                int R = a[j] - a[i];
                if (R <= 0) continue;
                // Greedy: partition into groups with range exactly R
                vector<bool> used(n, false);
                int groups = 0;
                bool ok = true;
                for (int k = 0; k < n && ok; k++) {
                    if (used[k]) continue;
                    int maxVal = a[k] + R;
                    bool hasMax = false;
                    int cnt = 0;
                    for (int l = k; l < n; l++) {
                        if (a[l] > maxVal) break;
                        if (a[l] == maxVal && !used[l]) hasMax = true;
                        if (!used[l]) cnt++;
                    }
                    if (!hasMax || cnt < 2) { ok = false; break; }
                    for (int l = k; l < n; l++) {
                        if (a[l] > maxVal) break;
                        if (!used[l]) used[l] = true;
                    }
                    groups++;
                }
                if (ok) {
                    for (int k = 0; k < n; k++) if (!used[k]) { ok = false; break; }
                }
                if (ok && groups >= 2) possible = true;
            }
        }
        cout << (possible ? "Yes" : "No") << "\n";
    }
    return 0;
}
