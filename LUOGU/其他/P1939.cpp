#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

vector<vector<long long>> mul(const vector<vector<long long>>& a, const vector<vector<long long>>& b) {
    vector<vector<long long>> c(3, vector<long long>(3, 0));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}

long long solve(long long n) {
    if (n <= 3) return 1;
    vector<vector<long long>> M = {{1,0,1},{1,0,0},{0,1,0}};
    vector<vector<long long>> R = {{1,0,0},{0,1,0},{0,0,1}};
    long long e = n - 3;
    while (e > 0) {
        if (e & 1) R = mul(R, M);
        M = mul(M, M);
        e >>= 1;
    }
    return (R[0][0] + R[0][1] + R[0][2]) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        cout << solve(n) << '\n';
    }
    return 0;
}
