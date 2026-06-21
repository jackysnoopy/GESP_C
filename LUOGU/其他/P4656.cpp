#include <iostream>
#include <algorithm>
using namespace std;
long long C[333][333], S[333][333];
void init() {
    C[0][0] = 1;
    for (int i = 1; i < 333; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % 3;
    }
    for (int i = 0; i < 333; i++) {
        S[i][0] = C[i][0];
        for (int j = 1; j < 333; j++)
            S[i][j] = (S[i][j-1] + C[i][j]) % 3;
    }
}
long long solve(long long n, long long k) {
    if (n < 0 || k < 0) return 0;
    if (n == 0) return 1;
    if (k >= n) return solve(n, n);
    long long p = 1;
    while (p * 3 <= n) p *= 3;
    long long np = n / p, nk = k / p;
    long long nr = n % p, kr = k % p;
    long long res = S[np][nk] * C[np > 0 ? np : 0][nk] % 3;
    // Actually using Lucas theorem mod 3
    res = S[np][nk % np] % 3;
    if (np > 0) res = res * solve(nr, kr) % 3;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        long long ans = solve(n, k);
        cout << ans % 3 << "\n";
    }
    return 0;
}
