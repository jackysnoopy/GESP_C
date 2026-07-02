#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<long long>> a(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    
    vector<vector<long long>> colSum(n + 1, vector<long long>(m + 1, 0));
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            colSum[i][j] = colSum[i - 1][j] + a[i][j];
    
    long long ans = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            vector<long long> prefix(m + 1, 0);
            for (int k = 1; k <= m; k++)
                prefix[k] = prefix[k - 1] + (colSum[j][k] - colSum[i - 1][k]);
            
            vector<int> stk;
            for (int k = 0; k <= m; k++) {
                if (stk.empty() || prefix[k] < prefix[stk.back()])
                    stk.push_back(k);
            }
            
            for (int k = m; k >= 1; k--) {
                while (stk.size() > 1 && prefix[stk[stk.size() - 2]] < prefix[k])
                    stk.pop_back();
                if (!stk.empty() && prefix[k] > prefix[stk.back()]) {
                    long long area = (long long)(j - i + 1) * (k - stk.back());
                    ans = max(ans, area);
                }
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}
