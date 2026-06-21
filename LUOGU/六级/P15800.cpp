#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    vector<int> dp(n, 1);
    int ans = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (j + b[j] <= i)
                dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    
    cout << ans << '\n';
    return 0;
}