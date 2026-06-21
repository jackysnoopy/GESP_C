#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long ans = 0;
    long long sum = 0;
    long long prod = 1;

    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            ans = max(ans, prod * sum % MOD);
            sum = 0;
            prod = 1;
        } else {
            sum += a[i];
            prod = prod * sum % MOD;
        }
    }
    ans = max(ans, prod * sum % MOD);

    cout << ans % MOD << "\n";
    return 0;
}
