#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // dp[i] = max stanzas ending at position i
    // Try each of 4 patterns for last stanza using positions j1<j2<j3<i
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        // Extend without forming new stanza
        dp[i + 1] = max(dp[i + 1], dp[i]);
        // Try forming a new stanza ending at i (using 4 positions)
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < j; k++) {
                for (int l = 0; l < k; l++) {
                    // AAAA
                    if (a[l] == a[k] && a[k] == a[j] && a[j] == a[i]) {
                        dp[i + 1] = max(dp[i + 1], dp[l] + 1);
                    }
                    // AABB
                    if (a[l] == a[k] && a[j] == a[i] && a[k] != a[j]) {
                        dp[i + 1] = max(dp[i + 1], dp[l] + 1);
                    }
                    // ABAB
                    if (a[l] == a[j] && a[k] == a[i] && a[l] != a[k]) {
                        dp[i + 1] = max(dp[i + 1], dp[l] + 1);
                    }
                    // ABBA
                    if (a[l] == a[i] && a[k] == a[j] && a[l] != a[k]) {
                        dp[i + 1] = max(dp[i + 1], dp[l] + 1);
                    }
                }
            }
        }
    }
    cout << dp[n] << "\n";
    return 0;
}
