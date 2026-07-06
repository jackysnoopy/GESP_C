#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    
    int ans = 0;
    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int x2 = x1; x2 < n; x2++) {
                for (int y2 = y1; y2 < m; y2++) {
                    bool ok = true;
                    for (int i = x1; i <= x2 && ok; i++)
                        for (int j = y1; j <= y2 && ok; j++)
                            if (a[i][j] == 0) ok = false;
                    if (ok) ans = max(ans, (x2 - x1 + 1) * (y2 - y1 + 1));
                }
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}