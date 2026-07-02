#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long x;
        cin >> n >> x;
        vector<long long> a(n);
        long long sum = 0;
        for (int i = 0; i < n; i++) { cin >> a[i]; sum += a[i]; }
        if (n == 1) {
            if (a[0] == x) cout << "NO\n";
            else cout << "YES\n" << a[0] << "\n";
            continue;
        }
        // Try to find a valid permutation
        // Simple strategy: if any element != x, put it first
        // Then arrange remaining to avoid prefix sum = x
        int first = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] != x) { first = i; break; }
        }
        if (first == -1) {
            // All elements equal x, prefix sum always x*k, impossible for n>=2
            cout << "NO\n";
            continue;
        }
        // Check if we can arrange remaining
        // Put a[first] first, then try to arrange rest
        vector<long long> ans;
        ans.push_back(a[first]);
        vector<long long> rem;
        for (int i = 0; i < n; i++) if (i != first) rem.push_back(a[i]);
        long long pref = a[first];
        bool ok = (pref != x);
        // Greedy: at each step, pick an element that doesn't make pref = x
        // If stuck, try swapping first element
        if (ok) {
            vector<long long> result;
            result.push_back(a[first]);
            vector<bool> used(n, false);
            used[first] = true;
            long long cur = a[first];
            for (int step = 1; step < n; step++) {
                bool found = false;
                for (int i = 0; i < n; i++) {
                    if (used[i]) continue;
                    if (cur + a[i] != x) {
                        used[i] = true;
                        cur += a[i];
                        result.push_back(a[i]);
                        found = true;
                        break;
                    }
                }
                if (!found) { ok = false; break; }
            }
            if (ok) {
                cout << "YES\n";
                for (int i = 0; i < n; i++) cout << result[i] << " \n"[i==n-1];
            } else {
                cout << "NO\n";
            }
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
