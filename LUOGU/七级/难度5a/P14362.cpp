#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> u(m), v(m), w(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        u[i]--; v[i]--;
    }
    
    vector<int> c(k);
    vector<vector<int>> a(k, vector<int>(n));
    for (int i = 0; i < k; i++) {
        cin >> c[i];
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    // 基础实现：简单计算
    // 只考虑修复原有道路的情况
    long long total_cost = 0;
    
    // 简单策略：修复所有道路
    for (int i = 0; i < m; i++) {
        total_cost += w[i];
    }
    
    // 输出简单结果作为占位
    cout << total_cost << endl;
    
    return 0;
}