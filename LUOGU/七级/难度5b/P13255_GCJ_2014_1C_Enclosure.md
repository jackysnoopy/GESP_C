# [GCJ 2014 #1C] Enclosure

## 题目描述

在 N×M 网格上放置最少的石头来围住至少 K 个交叉点。

## 输入格式

第一行 T，每组包含 N、M、K。

## 输出格式

Case #x: y，y 为最少石头数。

## 样例

```
2
4 5 8
3 5 11
```

输出：
```
Case #1: 6
Case #2: 8
```

## 解题思路

### 问题分析
石头围住的区域需要是封闭的。石头放在交叉点上，围住的区域内的交叉点（包括有石头的）都被计算。

### 核心思路
- 小数据集：枚举所有可能的石头布局
- 大数据集：尝试矩形和菱形围法，取最优
- 矩形围法：边长为 a×b，需要 2(a+b)-4 个石头，围住 a×b 个点
- 菱形围法：半径 d 的菱形需要约 4d 个石头，围住约 2d² 个点

### 算法流程
1. 枚举所有矩形和菱形围法
2. 取围住 ≥K 个点时石头数最少的方案

### 复杂度分析
- 时间：O(N×M×(N+M))
- 空间：O(1)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, M, K; cin >> N >> M >> K;
        cout << "Case #" << t << ": ";
        int ans = K;
        for (int r1 = 0; r1 < N; r1++)
            for (int c1 = 0; c1 < M; c1++)
                for (int r2 = r1; r2 < N; r2++)
                    for (int c2 = c1; c2 < M; c2++) {
                        int perimeter = 2*(r2-r1+1) + 2*(c2-c1+1) - 4;
                        int inner = (r2-r1>1 && c2-c1>1) ? (r2-r1-1)*(c2-c1-1) : 0;
                        if (inner + perimeter >= K) ans = min(ans, perimeter);
                    }
        for (int cr = 0; cr < N; cr++)
            for (int cc = 0; cc < M; cc++)
                for (int d = 0; d <= N+M; d++) {
                    int stones = 0, enclosed = 0;
                    for (int r = 0; r < N; r++)
                        for (int c = 0; c < M; c++)
                            if (abs(r-cr)+abs(c-cc) <= d) {
                                enclosed++;
                                if (abs(r-cr)+abs(c-cc) == d) stones++;
                            }
                    if (d == 0) stones = 1;
                    if (enclosed >= K) { ans = min(ans, stones); break; }
                }
        cout << ans << "\n";
    }
    return 0;
}
```
