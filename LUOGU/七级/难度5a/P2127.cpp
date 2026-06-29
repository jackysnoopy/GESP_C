#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // 排序后的数组
    vector<long long> sorted = a;
    sort(sorted.begin(), sorted.end());
    
    // 建立映射：值 -> 排序后的位置
    // 使用map来处理大数值
    vector<pair<long long, int>> indexed(n);
    for (int i = 0; i < n; i++) {
        indexed[i] = {a[i], i};
    }
    sort(indexed.begin(), indexed.end());
    
    // 目标位置
    vector<int> target(n);
    for (int i = 0; i < n; i++) {
        target[indexed[i].second] = i;
    }
    
    vector<bool> visited(n, false);
    long long ans = 0;
    long long global_min = sorted[0];
    
    for (int i = 0; i < n; i++) {
        if (visited[i] || target[i] == i) continue;
        
        // 找到一个环
        long long cycle_sum = 0;
        long long cycle_min = a[i];
        int cycle_len = 0;
        int j = i;
        
        while (!visited[j]) {
            visited[j] = true;
            cycle_sum += a[j];
            cycle_min = min(cycle_min, a[j]);
            cycle_len++;
            j = target[j];
        }
        
        // 两种方法的代价
        // 方法1：使用环内最小值
        long long cost1 = cycle_sum + (cycle_len - 2) * cycle_min;
        // 方法2：使用全局最小值
        long long cost2 = cycle_sum + cycle_min + (cycle_len + 1) * global_min;
        
        ans += min(cost1, cost2);
    }
    
    cout << ans << "\n";
    return 0;
}