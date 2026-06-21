#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, p, S;
vector<int> w, v;
int dp[1005];

bool check(int limit) {
    fill(dp, dp + S + 1, 0);
    for (int i = 0; i < n; i++) {
        if (w[i] > limit) continue;
        for (int j = S; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    for (int j = 0; j <= S; j++)
        if (dp[j] >= p) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> S;
    w.resize(n); v.resize(n);
    int maxW = 0;
    for (int i = 0; i < n; i++) { cin >> w[i] >> v[i]; maxW = max(maxW, w[i]); }
    // Binary search on minimum interface size
    int lo = 1, hi = maxW;
    bool found = false;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) { hi = mid - 1; found = true; }
        else lo = mid + 1;
    }
    if (!found) cout << "No Solution!\n";
    else cout << lo << "\n";
    return 0;
}
