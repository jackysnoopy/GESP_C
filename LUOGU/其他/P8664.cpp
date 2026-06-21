#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long S;
    if (!(cin >> n >> S)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long total = 0;
    for (long long x : a) total += x;
    if (total <= S) {
        cout << fixed << setprecision(4) << 0.0 << '\n';
        return 0;
    }
    vector<long long> b = a;
    sort(b.begin(), b.end());
    long long need = total - S;
    double base = (double)S / n;
    double ans = 0.0;
    long long cap = 0;
    for (int i = 0; i < n; ++i) {
        cap += b[i];
        double maxAllowed = base + (double)cap / (i + 1);
        if (maxAllowed <= b[i]) {
            long long left = total - S;
            long long rem = n - i;
            double base2 = (double)(total - left) / rem;
            for (int j = i; j < n; ++j) {
                double diff = base2 - b[j];
                ans += diff * diff;
            }
            break;
        }
    }
    ans = sqrt(ans / n);
    cout << fixed << setprecision(4) << ans << '\n';
    return 0;
}
