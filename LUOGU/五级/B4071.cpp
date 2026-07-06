#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    // 存储每种武器对应的材料花费
    vector<vector<int>> costs(n + 1);
    for (int i = 0; i < m; i++) {
        int p, c;
        cin >> p >> c;
        costs[p].push_back(c);
    }
    
    // 对每种武器的花费进行排序，便于后续取最小花费
    for (int i = 1; i <= n; i++) {
        sort(costs[i].begin(), costs[i].end());
    }
    
    long long ans = LLONG_MAX;
    int baseCnt = costs[1].size(); // 武器1的初始材料数量
    
    // 枚举最终武器1想要达到的数量 target
    // 下限为初始数量，上限为总材料数（最坏情况把所有材料都给武器1）
    for (int target = baseCnt; target <= m; target++) {
        long long curCost = 0;
        int curCnt1 = baseCnt; // 当前武器1的材料数量
        
        // 用于存储从其他武器拿走的材料花费（需要修改的材料）
        vector<int> needModify;
        
        // 第一步：处理其他武器，确保它们的材料数量 < target
        for (int i = 2; i <= n; i++) {
            int over = costs[i].size() - target + 1; // 需要修改掉的材料数量
            for (int j = 0; j < over && j < (int)costs[i].size(); j++) {
                curCost += costs[i][j]; // 花费最小的 over 个材料修改给武器1
                curCnt1++;
                // 这些被修改的材料原本属于武器i，现在变成武器1
            }
            // 剩余的材料（没被修改的）都保留在武器i，加入 needModify 供后续考虑
            // 注意：我们只修改了 over 个，剩下的如果后面需要给武器1，还需额外花费
            int start = max(0, over);
            for (int j = start; j < (int)costs[i].size(); j++) {
                needModify.push_back(costs[i][j]);
            }
        }
        
        // 如果当前武器1的数量已经 >= target，且满足严格大于条件（其他武器都 < target），则更新答案
        // 但此时其他武器可能等于 target-1 或更少，严格大于条件：curCnt1 > max(其他武器数量)
        // 我们的第一步已经保证其他武器数量都 <= target-1，所以如果 curCnt1 >= target 就满足严格大于
        if (curCnt1 >= target) {
            ans = min(ans, curCost);
            continue;
        }
        
        // 第二步：如果武器1数量还不够 target，需要从 needModify 中取最小花费的材料
        // 注意 needModify 存储的是所有未被修改的、属于其他武器的材料的花费
        sort(needModify.begin(), needModify.end());
        int need = target - curCnt1;
        if (need <= (int)needModify.size()) {
            for (int i = 0; i < need; i++) {
                curCost += needModify[i];
            }
            ans = min(ans, curCost);
        }
    }
    
    cout << ans << "\n";
    return 0;
}