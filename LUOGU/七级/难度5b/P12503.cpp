#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    long long x0, d;
    cin >> x0 >> d;
    sort(x.begin(), x.end());
    int m;
    cin >> m;
    while (m--) {
        long long t;
        cin >> t;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long target = x[i];
            long long k = (target - x0 + d - 1) / d;
            if (k < 0) k = (target - x0) / d;
            long long supply = x0 + k * d;
            ans += (supply - target) * (supply - target);
            ans += (k > 0 ? k : -k) * t;
            x0 = supply;
        }
        cout << ans << "\n";
    }
    return 0;
}
