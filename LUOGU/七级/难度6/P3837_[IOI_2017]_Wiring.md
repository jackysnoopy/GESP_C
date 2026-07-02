# P3837 [IOI 2017] Wiring

## 题目描述

You are given a set of $n$ wires and $m$ plugs. Each wire has a position on a line, and each plug has a position on a line. You need to connect each wire to exactly one plug, such that the total length of the wires is minimized.

Each wire can be connected to any plug, but the connection must be a straight line. The length of a wire is the distance between its position and the position of the plug it is connected to.

## 输入格式

第一行两个整数 $n, m$，表示电线和插头的数量。

接下来 $n$ 行，每行一个整数，表示电线的位置。

接下来 $m$ 行，每行一个整数，表示插头的位置。

## 输出格式

一个整数，表示最小的总长度。

## 样例

输入：
```
3 3
1
2
3
1
2
3
```
输出：
```
0
```

## 解题思路

### 问题分析

这是一个交互题DP问题。需要将电线连接到插头，使得总长度最小。

### 核心思路

1. 将电线和插头分别排序
2. 使用动态规划，$dp[i][j]$ 表示前 $i$ 根电线连接到前 $j$ 个插头的最小总长度
3. 状态转移：$dp[i][j] = \min(dp[i][j-1], dp[i-1][j-1] + |wire[i] - plug[j]|)$

### 算法流程

1. 读取电线和插头的位置
2. 分别排序
3. 使用动态规划计算最小总长度
4. 输出答案

### 复杂度分析

- 时间复杂度：$O(n \times m)$
- 空间复杂度：$O(n \times m)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> wire(n), plug(m);
    for (int i = 0; i < n; i++) cin >> wire[i];
    for (int i = 0; i < m; i++) cin >> plug[i];
    
    sort(wire.begin(), wire.end());
    sort(plug.begin(), plug.end());
    
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 1e18));
    dp[0][0] = 0;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1]);
            if (i > 0 && j > 0) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + abs(wire[i-1] - plug[j-1]));
            }
        }
    }
    
    cout << dp[n][m] << endl;
    return 0;
}
```
