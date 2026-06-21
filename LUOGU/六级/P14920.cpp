#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    ll k;
    cin >> n >> k;
    
    vector<int> a(n);
    vector<ll> c(n);
    int sum_a = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> c[i];
        sum_a += a[i];
    }
    
    const ll INF = 1e18;
    vector<ll> dp(sum_a + 1, INF);
    dp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = sum_a; j >= a[i]; j--) {
            if (dp[j - a[i]] != INF) {
                dp[j] = min(dp[j], dp[j - a[i]] + c[i]);
            }
        }
    }
    
    for (int j = sum_a; j >= 0; j--) {
        if (dp[j] <= k) {
            cout << j << '\n';
            break;
        }
    }
    
    return 0;
}
