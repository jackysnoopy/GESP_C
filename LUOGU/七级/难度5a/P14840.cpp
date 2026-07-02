#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

long long modpow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        
        if (n % l != 0 && n % r != 0) {
            cout << "-1\n";
            continue;
        }
        
        long long sum = 0;
        for (int j = 0; j < n; j++) {
            sum += a[j];
        }
        
        long long ans = sum * sum % MOD * modpow(n, MOD - 2, MOD) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}