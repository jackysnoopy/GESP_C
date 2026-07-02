#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> c[i];
        a[i]--; // 转换为0-indexed
    }
    
    // 基础实现：简单计算
    // 统计每个节点的入度
    vector<int> in_degree(n, 0);
    for (int i = 0; i < n; i++) {
        in_degree[a[i]]++;
    }
    
    // 找出入度为0的节点
    long long total_cost = 0;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            total_cost += c[i];
        }
    }
    
    // 输出简单结果作为占位
    cout << total_cost << endl;
    
    return 0;
}