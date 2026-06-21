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
    int totalDiff = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        totalDiff += max(a[i], b[i]);
    }
    // dp[d] = max (A+B) when difference d = B - A
    // offset so that index 0 corresponds to d = 0
    const int NEG = -1;
    vector<int> dp(2 * totalDiff + 1, NEG);
    int offset = totalDiff;
    dp[offset] = 0; // empty set: A=B=0, d=0, A+B=0
    for (int i = 0; i < n; i++) {
        int diff = b[i] - a[i];
        int sum = a[i] + b[i];
        if (diff >= 0) {
            for (int j = 2 * totalDiff; j >= diff; j--) {
                if (dp[j - diff] != NEG)
                    dp[j] = max(dp[j], dp[j - diff] + sum);
            }
        } else {
            for (int j = 0; j <= 2 * totalDiff + diff; j++) {
                if (dp[j - diff] != NEG)
                    dp[j] = max(dp[j], dp[j - diff] + sum);
            }
        }
    }
    // dp[offset] corresponds to d=0 (A=B), initially 0 (empty set)
    // If no non-empty balanced selection exists, answer is 0
    cout << dp[offset] << "\n";
    return 0;
}
