#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 5001;
int sum[MAXN+1][MAXN+1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        sum[x+1][y+1] += v;
    }
    
    for (int i = 1; i <= MAXN; i++)
        for (int j = 1; j <= MAXN; j++)
            sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
    
    int ans = 0;
    for (int i = m; i <= MAXN; i++) {
        for (int j = m; j <= MAXN; j++) {
            int val = sum[i][j] - sum[i-m][j] - sum[i][j-m] + sum[i-m][j-m];
            if (val > ans) ans = val;
        }
    }
    
    cout << ans << "\n";
    return 0;
}