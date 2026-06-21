#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Maximum sum subarray of length k
    long long sum = 0;
    for (int i = 0; i < k; i++) sum += a[i];
    long long ans = sum;
    for (int i = k; i < n; i++) {
        sum += a[i] - a[i-k];
        ans = max(ans, sum);
    }
    cout << ans << "\n";
    return 0;
}
