#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long dp0 = 0, dp1 = 0;
    for (int i = 0; i < n; i++) {
        long long ndp0 = max(dp0, dp1);
        long long ndp1 = dp0 + a[i];
        dp0 = ndp0;
        dp1 = ndp1;
    }
    cout << max(dp0, dp1) << "\n";
    return 0;
}
