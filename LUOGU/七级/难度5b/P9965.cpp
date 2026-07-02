#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n), b(n), c(n);
    long long total_a = 0, total_c = 0, total_S = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        total_a += a[i];
        total_c += c[i];
        if (a[i] >= 1) {
            total_S += min(b[i], a[i] + c[i]);
        }
    }

    long long max_total = total_a + total_c;

    for (int i = 0; i < n; i++) {
        long long S = total_S;
        if (a[i] >= 1) {
            S -= min(b[i], a[i] + c[i]);
        }

        long long max_balls;
        if (a[i] + S >= 1) {
            max_balls = a[i] + c[i] + S;
        } else {
            max_balls = 0;
        }

        cout << max_balls << (i + 1 < n ? " " : "\n");
    }
    cout << max_total << "\n";

    return 0;
}
