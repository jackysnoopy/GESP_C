#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const long long MOD = 1000000007;

struct Mat {
    int n;
    vector<vector<long long>> a;
    Mat(int n) : n(n), a(n, vector<long long>(n, 0)) {}
    Mat operator*(const Mat& o) const {
        Mat r(n);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k) if (a[i][k])
                for (int j = 0; j < n; ++j)
                    r.a[i][j] = (r.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
        return r;
    }
};

Mat power(Mat m, long long e) {
    int n = m.n;
    Mat r(n);
    for (int i = 0; i < n; ++i) r.a[i][i] = 1;
    while (e > 0) {
        if (e & 1) r = r * m;
        m = m * m;
        e >>= 1;
    }
    return r;
}

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;
    cin >> n >> m >> k;
    int total = n * m;
    vector<string> grid(n);
    vector<vector<int>> ops(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) ops[i][j] = grid[i][j] - '0';
    }
    vector<int> len(total);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int v = ops[i][j];
            if (v <= 1) len[i * m + j] = 1;
            else len[i * m + j] = v;
        }
    long long lcm_all = 1;
    for (int i = 0; i < total; ++i)
        lcm_all = lcm_all / gcd(lcm_all, len[i]) * len[i];
    
    Mat result(total + 1);
    for (int i = 0; i < total; ++i) result.a[i][i] = 1;
    result.a[total][total] = 1;
    
    for (int t = 0; t < lcm_all && t < k; ++t) {
        Mat trans(total + 1);
        for (int i = 0; i < total; ++i) trans.a[i][i] = 1;
        trans.a[total][total] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                int idx = i * m + j;
                int v = ops[i][j];
                int nr = i, nc = j;
                if (v == 0) nc = (j + 1) % m;
                else if (v == 1) nc = (j - 1 + m) % m;
                else if (v == 2) nr = (i - 1 + n) % n;
                else if (v == 3) nr = (i + 1) % n;
                else if (v == 4) { nr = (i - 1 + n) % n; nc = (j - 1 + m) % m; }
                else if (v == 5) { nr = (i + 1) % n; nc = (j + 1) % m; }
                else if (v == 6) { nr = (i - 1 + n) % n; nc = (j + 1) % m; }
                else if (v == 7) { nr = (i + 1) % n; nc = (j - 1 + m) % m; }
                int nidx = nr * m + nc;
                trans.a[nidx][idx] = (trans.a[nidx][idx] + 1) % MOD;
                trans.a[total][idx] = (trans.a[total][idx] + 1) % MOD;
            }
        result = trans * result;
    }
    long long rem = k % lcm_all;
    if (rem > 0) {
        Mat trans(total + 1);
        for (int i = 0; i < total; ++i) trans.a[i][i] = 1;
        trans.a[total][total] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                int idx = i * m + j;
                int v = ops[i][j];
                int nr = i, nc = j;
                if (v == 0) nc = (j + 1) % m;
                else if (v == 1) nc = (j - 1 + m) % m;
                else if (v == 2) nr = (i - 1 + n) % n;
                else if (v == 3) nr = (i + 1) % n;
                int nidx = nr * m + nc;
                trans.a[nidx][idx] = (trans.a[nidx][idx] + 1) % MOD;
                trans.a[total][idx] = (trans.a[total][idx] + 1) % MOD;
            }
        result = power(trans, rem) * result;
    }
    cout << result.a[total][0] << '\n';
    return 0;
}
