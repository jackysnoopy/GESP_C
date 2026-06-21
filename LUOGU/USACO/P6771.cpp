#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> h(N), a(N), c(N);
    for (int i = 0; i < N; i++) cin >> h[i] >> a[i] >> c[i];
    vector<int> order(N);
    for (int i = 0; i < N; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) { return a[i] < a[j]; });
    vector<int> dp(40001, 0);
    for (int idx : order) {
        for (int k = 0; k < c[idx]; k++) {
            for (int j = a[idx]; j >= h[idx]; j--) {
                dp[j] = max(dp[j], dp[j - h[idx]] + h[idx]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= 40000; i++) ans = max(ans, dp[i]);
    cout << ans << "\n";
    return 0;
}
