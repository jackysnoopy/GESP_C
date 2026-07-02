#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    
    vector<vector<int>> p(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }
    
    // 简单贪心：按重要度从大到小选择实验
    vector<int> order;
    vector<bool> done(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        if (!done[i]) {
            order.push_back(i);
            done[i] = true;
            if (order.size() == n - m) break;
        }
    }
    
    for (int i = 0; i < order.size(); i++) {
        if (i > 0) cout << " ";
        cout << order[i];
    }
    cout << "\n";
    
    return 0;
}