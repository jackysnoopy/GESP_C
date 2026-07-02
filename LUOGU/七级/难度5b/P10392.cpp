#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long k;
    cin >> n >> k;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 记录每个宝石是否已使用
    vector<bool> used(n, false);
    
    // 记录盒子中的宝石
    vector<long long> result(n, -1);
    
    // 从前往后处理每个盒子
    for (int box = 0; box < n; box++) {
        // 尝试放入魔力值最大的可用宝石
        // 但要满足体力限制和相邻约束
        
        long long bestGem = -1;
        int bestIdx = -1;
        
        // 找到魔力值最大的可用宝石
        for (int gem = 0; gem < n; gem++) {
            if (used[gem]) continue;
            
            // 检查体力限制
            long long cost = (gem + 1) - (box + 1); // 宝石位置 - 盒子位置
            if (cost < 0) continue; // 宝石位置必须 >= 盒子位置
            
            // 检查相邻约束
            if (box > 0 && result[box - 1] != -1 && a[gem] == result[box - 1]) {
                continue;
            }
            
            // 更新最优选择
            if (a[gem] > bestGem) {
                bestGem = a[gem];
                bestIdx = gem;
            }
        }
        
        if (bestIdx != -1) {
            long long cost = (bestIdx + 1) - (box + 1);
            if (cost <= k) {
                result[box] = bestGem;
                used[bestIdx] = true;
                k -= cost;
            }
        }
    }
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
    
    return 0;
}
