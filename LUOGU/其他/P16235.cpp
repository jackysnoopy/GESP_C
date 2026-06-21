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
        int n;
        cin >> n;
        vector<int> a(n);
        int total = 0;
        for (int i = 0; i < n; i++) { cin >> a[i]; total += a[i]; }
        if (total % 5 != 0 || total / 5 < n) { cout << "F\n"; continue; }
        int teams = total / 5;
        // Each team has 5 different positions. We have n types.
        // Max from any type = teams. Need a[i] <= teams for all i.
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (a[i] > teams) { ok = false; break; }
        }
        cout << (ok ? "T\n" : "F\n");
    }
    return 0;
}
