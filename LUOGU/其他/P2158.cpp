#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    if (n == 1) { cout << 1 << '\n'; return 0; }
    if (n == 2) { cout << 3 << '\n'; return 0; }
    vector<int> phi(n + 1);
    vector<bool> is_comp(n + 1, false);
    for (int i = 1; i <= n; ++i) phi[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (!is_comp[i]) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
                if (j > i) is_comp[j] = true;
            }
        }
    }
    long long ans = 3;
    for (int i = 3; i < n; ++i) ans += 2LL * phi[i];
    cout << ans << '\n';
    return 0;
}
