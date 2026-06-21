#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    vector<long long> w(n);
    for (int i = 0; i < n; i++) {
        w[i] = a[i] % MOD * ((i + 1) % MOD) % MOD * ((n - i) % MOD) % MOD;
    }
    
    sort(w.begin(), w.end(), greater<long long>());
    sort(b.begin(), b.end());
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + w[i] % MOD * (b[i] % MOD)) % MOD;
    }
    
    cout << ans << "\n";
    return 0;
}
