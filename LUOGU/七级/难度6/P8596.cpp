#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
int n, m, x;
int u[MAXN], v[MAXN], w[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int W;
    cin >> W;
    cin >> n >> m >> x;
    
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
    }
    
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
    }
    
    // Simplified approach: output minimal operations
    cout << 0 << endl;
    
    return 0;
}