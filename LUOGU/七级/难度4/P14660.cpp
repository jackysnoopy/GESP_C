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

        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

        bool all_ok = true;
        vector<int> bad;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                all_ok = false;
                bad.push_back(i);
            }
        }

        if (all_ok) {
            cout << "YES\n";
            continue;
        }

        if (bad.size() == n) {
            cout << "NO\n";
            continue;
        }

        long long sum_a = 0, sum_b = 0;
        for (int i = 0; i < n; i++) {
            sum_a += a[i];
            sum_b += b[i];
        }

        double avg = (double)sum_a / n;
        bool ok = true;
        for (int i : bad) {
            if (avg > b[i]) {
                ok = false;
                break;
            }
        }

        cout << (ok ? "YES" : "NO") << "\n";
    }

    return 0;
}
