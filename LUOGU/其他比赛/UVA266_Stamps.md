# UVA266 - Stamps (邮票问题)

## 题目描述

给定若干邮票面值和目标邮资，求组成目标邮资所需的最少邮票数量。

## 输入格式

- 每组数据第一行是邮票面值数量 `n`
- 接下来 `n` 行是每种邮票的面值
- 之后是若干个目标邮资，以 `0` 结束
- 以 `0` 表示所有数据结束

## 输出格式

- 对每个目标邮资，输出组成该邮资所需的最少邮票数量
- 若无法组成则输出"无法组成目标面值"

## 解题思路

### 核心算法：完全背包/动态规划

1. **状态定义**：`dp[i]` 表示组成面值 `i` 所需的最少邮票数量
2. **状态转移**：`dp[i] = min(dp[i], dp[i - stamp] + 1)` 对所有邮票面值
3. **边界条件**：`dp[0] = 0`

### 算法流程

1. 读取所有邮票面值并排序
2. 初始化 `dp` 数组，`dp[0] = 0`，其余为无穷大
3. 对每个目标邮资，从 1 到目标值进行状态转移
4. 输出 `dp[target]`

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<int> stamps(n);
        for (int i = 0; i < n; i++) {
            cin >> stamps[i];
        }
        sort(stamps.begin(), stamps.end());
        
        int target;
        while (cin >> target && target != 0) {
            int dp[10001];
            fill(dp, dp + 10001, 10000);
            dp[0] = 0;
            
            for (int v = 1; v <= target; v++) {
                for (int s : stamps) {
                    if (s > v) break;
                    if (dp[v - s] + 1 < dp[v]) {
                        dp[v] = dp[v - s] + 1;
                    }
                }
            }
            
            if (dp[target] < 10000) {
                cout << dp[target] << endl;
            } else {
                cout << "无法组成目标面值" << endl;
            }
        }
    }
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：O(n × target)，其中 n 是邮票种类数
- **空间复杂度**：O(target)

## 注意事项

1. 使用完全背包思想，每种邮票可以使用多次
2. 先排序可以提前终止内层循环
3. 使用较大的初始值（如 10000）表示不可达状态
4. 输出中文提示信息
