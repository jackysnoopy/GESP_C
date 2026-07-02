#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i];
    }
    
    cout << ans % MOD << endl;
    return 0;
}