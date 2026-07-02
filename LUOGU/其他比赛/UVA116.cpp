#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        
        vector<vector<long long>> dp(m, vector<long long>(n, LLONG_MAX));
        vector<vector<int>> path(m, vector<int>(n, -1));
        
        for (int i = 0; i < m; i++) dp[i][0] = grid[i][0];
        
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < m; i++) {
                int up = (i - 1 + m) % m;
                int down = (i + 1) % m;
                
                vector<pair<long long, int>> candidates;
                candidates.push_back({dp[i][j - 1], i});
                candidates.push_back({dp[up][j - 1], up});
                candidates.push_back({dp[down][j - 1], down});
                
                sort(candidates.begin(), candidates.end());
                
                if (dp[i][j] > candidates[0].first + grid[i][j]) {
                    dp[i][j] = candidates[0].first + grid[i][j];
                    path[i][j] = candidates[0].second;
                }
            }
        }
        
        int bestRow = 0;
        for (int i = 1; i < m; i++) {
            if (dp[i][n - 1] < dp[bestRow][n - 1]) bestRow = i;
        }
        
        vector<int> route(n);
        int cur = bestRow;
        for (int j = n - 1; j >= 0; j--) {
            route[j] = cur + 1;
            cur = path[cur][j];
        }
        
        for (int i = 0; i < n; i++) {
            if (i) cout << " ";
            cout << route[i];
        }
        cout << "\n" << dp[bestRow][n - 1] << "\n";
    }
    return 0;
}
