# UVA153 - Perambulating Elephants (行走的大象)

## 题目描述

在一个有障碍物的网格世界中，大象从 (1,1) 移动到 (M,N)，只能向右或向下移动。某些单元格被阻挡（#）。计算总路径数模 10000。输入 M N 后跟 M 行 N 个字符。'.'=开放，'#'=阻挡。输出路径数。

## 解题思路

### 问题分析

这是一个经典的动态规划问题，类似于机器人走格子问题，但增加了障碍物。

### 核心思路

使用动态规划，dp[i][j] 表示从 (1,1) 到 (i,j) 的路径数。转移方程为 dp[i][j] = dp[i-1][j] + dp[i][j-1]，但如果当前格是障碍物则 dp[i][j] = 0。

### 算法流程

1. 读取网格
2. 初始化 dp 表
3. 如果起点是障碍物，结果为 0
4. 否则 dp[0][0] = 1
5. 逐行逐列填充 dp 表
6. 输出 dp[M-1][N-1]

### 复杂度分析

- 时间复杂度：O(M*N)
- 空间复杂度：O(M*N)

## 代码实现

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    while (cin >> M >> N) {
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }

        vector<vector<int>> dp(M, vector<int>(N, 0));

        if (grid[0][0] == '.') {
            dp[0][0] = 1;
        }

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '#') {
                    dp[i][j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) continue;
                int fromTop = (i > 0) ? dp[i - 1][j] : 0;
                int fromLeft = (j > 0) ? dp[i][j - 1] : 0;
                dp[i][j] = (fromTop + fromLeft) % 10000;
            }
        }

        cout << dp[M - 1][N - 1] << "\n";
    }

    return 0;
}
```
