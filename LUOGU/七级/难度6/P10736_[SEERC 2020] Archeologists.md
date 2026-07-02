# [SEERC 2020] Archeologists

## 题目描述

你在玩一个寻宝类游戏，一共有 n 个格子，编号为 1~n，你每在 i 号格子上下挖一层便会获得 pi 的价值，其中你需要保证每个格子相邻的两个格子都与其下挖的深度的差值不超过 1，请最大化总价值。

## 输入格式

第一行一个整数 n (1≤n≤2.5×10^5)。
接下来一行 n 个整数 pi (-10^6≤pi≤10^6)。

## 输出格式

输出最大价值。

## 样例

### 样例 1
输入：
```
5
1 3 -4 2 1
```
输出：
```
8
```

### 样例 2
输入：
```
4
1 1 -2 3
```
输出：
```
5
```

### 样例 3
输入：
```
5
-1 -3 0 -5 -4
```
输出：
```
0
```

## 提示

对于 100% 的数据，1≤n≤2.5×10^5，-10^6≤pi≤10^6。

## 解题思路

### 问题分析
需要在相邻格子深度差不超过1的约束下最大化总价值。

### 核心思路
动态规划，定义每个格子挖0、1、2层的状态。

### 算法流程
1. 定义dp[i][j]表示前i个格子，第i个格子挖j层的最大价值
2. 状态转移：dp[i][0] = max(dp[i-1][0], dp[i-1][1])
3. dp[i][1] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2])) + pi
4. dp[i][2] = dp[i-1][2] + 2*pi

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 250005;
int n;
long long p[MAXN];
long long dp[MAXN][3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
    }
    
    dp[1][0] = 0;
    dp[1][1] = p[1];
    dp[1][2] = 2 * p[1];
    
    for (int i = 2; i <= n; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        dp[i][1] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2])) + p[i];
        dp[i][2] = dp[i-1][2] + 2 * p[i];
    }
    
    long long ans = max(dp[n][0], max(dp[n][1], dp[n][2]));
    printf("%lld\n", ans);
    
    return 0;
}
```