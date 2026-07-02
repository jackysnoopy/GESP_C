#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    int size = 2 * n + 1;
    vector<int> a(size);
    for (int i = 0; i < size; i++) cin >> a[i];
    
    // 二分答案：最长连续评分长度
    // 对于给定的长度L，检查是否能选出n+1个食材使得最长连续>=L
    
    // 贪心：每次选中间元素，删除一个元素
    // 这等价于在序列中选n+1个位置
    
    // 检查是否能得到长度>=L的连续评分
    auto check = [&](int L) -> bool {
        // 需要找到长度为L的连续评分区间[v, v+L-1]
        // 使得至少n+1个选中的食材的评分在[v, v+L-1]中
        // 且选中方式合法
        
        // 简化：检查是否存在连续L个评分，使得它们在序列中的位置满足选择条件
        // 选择条件：每次选中间，删一个
        // 这等价于：选出的n+1个位置中，任意相邻两个选中位置之间最多有1个未选中位置
        
        // 实际上，选择n+1个位置的方式是：
        // 从2n+1个位置中选n+1个，每次选中间删一个
        // 这等价于：选中的位置集合S满足|S|=n+1，且S的补集T满足
        // T中任意连续段的长度<=某个值
        
        // 更简单的理解：每次操作选中间删一个，相当于在序列上做选择
        // 选n+1个位置等价于：对于每个位置i，如果选中，则它左右未选中的位置数之和<=n
        
        // 简单贪心：对于每个可能的连续评分区间，检查能否选中足够多的食材
        for (int v = 1; v + L - 1 <= size; v++) {
            // 评分区间[v, v+L-1]
            // 找这些评分在序列中的位置
            vector<int> positions;
            for (int i = 0; i < size; i++) {
                if (a[i] >= v && a[i] <= v + L - 1) {
                    positions.push_back(i);
                }
            }
            
            if ((int)positions.size() < L) continue;
            
            // 检查能否从positions中选出L个使得选择合法
            // 合法条件：对于选中的L个位置，任意相邻两个之间最多有1个未选中位置
            // 这等价于：选中的位置在原序列中是"密集"的
            
            // 简单贪心：取positions中连续的L个，检查是否满足条件
            for (int j = 0; j + L - 1 < (int)positions.size(); j++) {
                // 检查positions[j..j+L-1]是否可以被选中
                // 选中L个位置，总共2n+1个位置，删n个
                // 合法条件：对于每个选中的位置，它左右的未选中位置数之和<=n
                
                // 简化：选中L个位置后，剩下的2n+1-L个位置中
                // 任意连续段的长度<=某个值
                // 实际上，只要L>=n+1，就一定可以选中
                
                if (L >= n + 1) return true;
                
                // 更精确的检查
                // 选中positions[j..j+L-1]这L个位置
                // 需要检查是否可以再选n+1-L个其他位置
                // 使得总共n+1个位置满足选择条件
                
                // 选择条件：每次选中间删一个
                // 等价于：选中的位置集合S满足
                // 对于S中任意相邻两个位置a,b，b-a<=2（即最多隔一个未选中位置）
                
                bool ok = true;
                for (int t = j; t < j + L - 1; t++) {
                    if (positions[t + 1] - positions[t] > 2) {
                        ok = false;
                        break;
                    }
                }
                
                if (ok) return true;
            }
        }
        return false;
    };
    
    int lo = 1, hi = n + 1, ans = 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
