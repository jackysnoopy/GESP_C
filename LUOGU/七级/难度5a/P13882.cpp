#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> Dis(n), Cost(n), Lim(n);
    for (int i = 0; i < n; i++) {
        cin >> Dis[i] >> Cost[i] >> Lim[i];
    }
    
    // 基础实现：简单贪心
    long long total_cost = 0;
    int current_fuel = m;
    
    for (int i = 0; i < n; i++) {
        // 需要消耗的油量
        if (current_fuel < Dis[i]) {
            // 油不够，无法完成旅行
            cout << -1 << endl;
            return 0;
        }
        
        current_fuel -= Dis[i];
        
        // 在当前加油站加油
        // 简单策略：加满到容量限制
        int can_add = min(Lim[i], m - current_fuel);
        total_cost += (long long)can_add * Cost[i];
        current_fuel += can_add;
    }
    
    cout << total_cost << endl;
    
    return 0;
}