#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    long long ans = 1;
    const long long MOD = 998244353;

    for (int i = 0; i < n; i++) {
        ans = ans * ((a[i] + m * b[i]) % MOD) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
