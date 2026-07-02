#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    while (cin >> M >> N) {
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }

        vector<vector<int>> dp(M, vector<int>(N, 0));

        if (grid[0][0] == '.') {
            dp[0][0] = 1;
        }

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '#') {
                    dp[i][j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) continue;
                int fromTop = (i > 0) ? dp[i - 1][j] : 0;
                int fromLeft = (j > 0) ? dp[i][j - 1] : 0;
                dp[i][j] = (fromTop + fromLeft) % 10000;
            }
        }

        cout << dp[M - 1][N - 1] << "\n";
    }

    return 0;
}
