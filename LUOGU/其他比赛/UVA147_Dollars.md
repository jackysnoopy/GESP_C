# UVA147 - Dollars (美元)

## 题目描述
经典硬币找零问题：给定面值为100,50,20,10,5,2,1美元的硬币，计算给定金额的找零方法数。
输入为美元金额（如14.65），输出为方法数。

## 解题思路

### 问题分析
这是一个典型的完全背包问题，计算凑成特定金额的方法数。

### 核心思路
使用动态规划，dp[i]表示凑成金额i的方法数。

### 算法流程
1. 初始化dp数组，dp[0]=1。
2. 按顺序处理每种面值的硬币。
3. 对于每种面值，从小到大更新dp数组。
4. 对于每个查询，将金额转换为分（整数），输出对应的方法数。

### 复杂度分析
- 时间复杂度：O(n*7)，其中n是最大金额（30000分）。
- 空间复杂度：O(n)。

## 代码实现
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

const int denominations[7] = {100, 50, 20, 10, 5, 2, 1};
long long dp[30001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int coin : denominations) {
        for (int amount = coin; amount <= 30000; ++amount) {
            dp[amount] += dp[amount - coin];
        }
    }

    double amount;
    while (cin >> amount && amount > 0.001) {
        int cents = static_cast<int>(amount * 100 + 0.5);
        cout << setw(6) << fixed << setprecision(2) << amount 
             << setw(17) << dp[cents] << endl;
    }

    return 0;
}
```
