#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int A, B, N;
    cin >> A >> B >> N;
    vector<int> pos = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};
    for (int i = 0; i < N; i++) {
        int m; cin >> m;
        pos.push_back(m);
    }
    sort(pos.begin(), pos.end());
    int sz = pos.size();
    vector<long long> dp(sz, 0);
    dp[0] = 1;
    for (int i = 1; i < sz; i++) {
        for (int j = i - 1; j >= 0; j--) {
            int d = pos[i] - pos[j];
            if (d < A) break;
            if (d > B) continue;
            dp[i] += dp[j];
        }
    }
    cout << dp[sz - 1] << "\n";
    return 0;
}
