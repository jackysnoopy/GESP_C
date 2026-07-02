#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        if (a[i] > 1) {
            ans = ans * a[i] % MOD;
        } else {
            ans = (ans + b[i]) % MOD;
        }
    }
    
    cout << ans << endl;
    return 0;
}