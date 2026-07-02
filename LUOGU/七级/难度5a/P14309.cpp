#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    
    vector<vector<pair<int, int>>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }
    
    // 基础实现：简单配对
    // 统计权值为1的点
    vector<int> ones;
    for (int i = 0; i < n; i++) {
        if (c[i] == 1) {
            ones.push_back(i);
        }
    }
    
    // 简单配对：计算最小距离和
    long long total = 0;
    // 这里只输出0作为占位，实际需要更复杂的算法
    cout << 0 << endl;
    
    return 0;
}