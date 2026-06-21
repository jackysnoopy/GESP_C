#include <iostream>
#include <vector>
using namespace std;
const int MOD = 100000000;
struct Mat {
    int n; vector<vector<long long>> a;
    Mat(int n) : n(n), a(n, vector<long long>(n, 0)) {}
};
Mat mul(const Mat &x, const Mat &y) {
    Mat r(x.n);
    for (int i = 0; i < x.n; ++i)
        for (int k = 0; k < x.n; ++k) if (x.a[i][k])
            for (int j = 0; j < x.n; ++j)
                r.a[i][j] = (r.a[i][j] + x.a[i][k] * y.a[k][j]) % MOD;
    return r;
}
Mat power(Mat m, long long e) {
    int n = m.n; Mat r(n);
    for (int i = 0; i < n; ++i) r.a[i][i] = 1;
    while (e > 0) { if (e & 1) r = mul(r, m); m = mul(m, m); e >>= 1; }
    return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    int d = n + 2;
    Mat T(d);
    for (int i = 0; i < n; ++i) T.a[i][i] = 1;
    for (int i = 0; i < n; ++i) T.a[i][i + 1] = 1;
    T.a[n][n] = 10; T.a[n][n + 1] = 1;
    T.a[d - 1][d - 1] = 1;
    for (int i = 0; i < n; ++i) T.a[i][d - 1] = 1;
    T = power(T, m);
    vector<long long> init(d, 0);
    init[0] = 23 % MOD;
    for (int i = 1; i < n; ++i) init[i] = (init[i - 1] * 10 + 3) % MOD;
    init[n] = 23; init[d - 1] = 1;
    long long ans = 0;
    for (int i = 0; i < d; ++i) ans = (ans + T.a[n][i] * init[i]) % MOD;
    cout << ans << '\n';
    return 0;
}
