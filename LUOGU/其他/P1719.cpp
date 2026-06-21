#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> a(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    
    int ans = INT_MIN;
    for (int x1 = 1; x1 <= n; x1++)
        for (int y1 = 1; y1 <= n; y1++)
            for (int x2 = x1; x2 <= n; x2++)
                for (int y2 = y1; y2 <= n; y2++) {
                    int sum = a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1];
                    ans = max(ans, sum);
                }
    
    cout << ans << "\n";
    return 0;
}