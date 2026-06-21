#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long n; cin >> n;
    vector<int> phi(n + 1);
    vector<bool> comp(n + 1, false);
    for (int i = 1; i <= n; ++i) phi[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (!comp[i]) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
                if (j > i) comp[j] = true;
            }
        }
    }
    vector<long long> sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + phi[i];
    long long ans = 0;
    for (int p = 2; p <= n; ++p) {
        if (!comp[p]) ans += sum[n / p] * 2 - 1;
    }
    cout << ans << '\n';
    return 0;
}
