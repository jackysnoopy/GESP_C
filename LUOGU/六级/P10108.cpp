#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> a(M);
    for (int i = 0; i < M; i++) cin >> a[i];

    vector<int> b(N);
    for (int i = 0; i < N; i++) cin >> b[i];

    vector<int> dp(N + 1, 0);

    for (int i = N - 1; i >= 0; i--) {
        int best = -2e9;
        for (int j = 0; j < M; j++) {
            int nxt = i + a[j];
            int val = (nxt >= N) ? 0 : dp[nxt];
            best = max(best, val);
        }
        dp[i] = b[i] + best;
    }

    cout << dp[0] << endl;
    return 0;
}
