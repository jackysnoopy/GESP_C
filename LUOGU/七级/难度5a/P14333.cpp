#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    // 基础实现：简单计算
    // 计算总检查项目数
    long long total_tasks = 0;
    for (int i = 0; i < n; i++) {
        total_tasks += b[i];
    }
    
    // 简单策略：每个工人平均分配任务
    long long tasks_per_worker = (total_tasks + k - 1) / k;
    
    // 计算最远距离
    long long max_distance = a[n - 1];
    
    // 输出简单结果作为占位
    cout << max_distance + tasks_per_worker << endl;
    
    return 0;
}