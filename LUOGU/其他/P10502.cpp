#include <iostream>
#include <vector>
using namespace std;
struct Mat {
    int n; long long mod;
    vector<vector<long long>> a;
    Mat(int n, long long mod) : n(n), mod(mod), a(n, vector<long long>(n, 0)) {}
};
Mat mul(const Mat &x, const Mat &y) {
    Mat r(x.n, x.mod);
    for (int i = 0; i < x.n; ++i)
        for (int k = 0; k < x.n; ++k) if (x.a[i][k])
            for (int j = 0; j < x.n; ++j)
                r.a[i][j] = (r.a[i][j] + x.a[i][k] * y.a[k][j]) % x.mod;
    return r;
}
Mat power(Mat m, long long e) {
    int n = m.n; Mat r(n, m.mod);
    for (int i = 0; i < n; ++i) r.a[i][i] = 1;
    while (e > 0) { if (e & 1) r = mul(r, m); m = mul(m, m); e >>= 1; }
    return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long k, m;
    cin >> n >> k >> m;
    Mat A(n, m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> A.a[i][j];
    int sz = 2 * n;
    Mat B(sz, m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) B.a[i][j] = A.a[i][j];
    for (int i = 0; i < n; ++i) B.a[i][i + n] = 1;
    for (int i = 0; i < n; ++i) B.a[i + n][i + n] = 1;
    B = power(B, k);
    // B^k 右上角 = I + A + ... + A^{k-1}
    // S = A + A^2 + ... + A^k = A * (I + A + ... + A^{k-1})
    Mat T(n, m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) T.a[i][j] = B.a[i][j + n];
    Mat S = mul(A, T);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';
            cout << S.a[i][j];
        }
        cout << '\n';
    }
    return 0;
}
