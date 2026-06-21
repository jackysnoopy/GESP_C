#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> d2(n + 5, 0);
    while (m--) {
        int l, r;
        long long s, e;
        cin >> l >> r >> s >> e;
        long long d = (e - s) / (r - l);
        d2[l] += s;
        d2[l+1] += d - s;
        d2[r+1] -= e + d;
        d2[r+2] += e;
    }
    for (int i = 1; i <= n; i++) d2[i] += d2[i-1];
    for (int i = 1; i <= n; i++) d2[i] += d2[i-1];
    long long mx = 0, xr = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, d2[i]);
        xr ^= d2[i];
    }
    cout << xr << " " << mx << "\n";
    return 0;
}
