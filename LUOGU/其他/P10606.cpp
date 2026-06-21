#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    int max_x = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        max_x = max(max_x, x);
    }
    
    int ans = 2e9 + 7;
    for (int i = max_x; i <= n; i++) {
        ans = min(ans, a[i]);
    }
    
    cout << ans << endl;
    return 0;
}
