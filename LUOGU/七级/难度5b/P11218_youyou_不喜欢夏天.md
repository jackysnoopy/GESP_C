# youyou 不喜欢夏天

## 题目描述

youyou 有一个大小为 $2 \times n$ 的网格，每个格子可能是黑色或者白色。

现在 youyou 和 yy 要在这个网格上玩一个游戏：
- youyou 先选取出一个可以为空的**连通块**
- 之后 yy 可以选择网格中最多 $m$ 列，将这些列上下行的格子颜色互换

youyou 希望最大化最终连通块中黑色格子减白色格子的数量，而 yy 希望最小化之。

在双方都采用最优策略的情况下，最终连通块黑色格子减白色格子的数量是多少？

## 输入格式

第一行为两个整数 $c,T$，分别表示测试点编号和数据组数。

对于每一组测试数据，第一行为两个整数 $n,m$。

接下来两行，每行用一个长度为 $n$ 的 $01$ 串表示颜色，$1$ 表示黑色，$0$ 表示白色。

## 输出格式

对于每一组测试数据，输出一行一个数。

## 样例

**样例输入：**
```
0 2
5 2
11110
01001
7 1
1110000
0001111
```

**样例输出：**
```
2
4
```

## 提示

- 测试点 $1\sim 3$：$\sum n \le 18$
- 测试点 $4\sim 7$：$\sum n \le 100$
- 测试点 $8\sim 9$：$\sum n \le 10^3$
- 测试点 $10\sim 11$：$\sum n \le 2\times 10^5$
- 测试点 $12\sim 25$：$\sum n \le 2\times 10^6$

特殊性质 A：不存在上下两格一黑一白的列。
特殊性质 B：不存在上下两格均黑色的列。
特殊性质 C：不存在上下两格均白色的列。

## 解题思路

### 问题分析

2×n 网格博弈问题。youyou 选择连通块，yy 可以交换最多 $m$ 列的上下颜色。需要求双方最优策略下的结果。

### 核心思路

对每列，定义四种类型：
- (0,0)：两白，贡献 -2
- (1,1)：两黑，贡献 +2  
- (0,1) 或 (1,0)：一黑一白，贡献 0

yy 最多交换 $m$ 列，会优先交换使结果最小化的列。youyou 需要选择一个连通块使得在 yy 最优应对下结果最大。

### 算法流程

1. 分析每列的类型和贡献
2. 考虑 yy 交换策略下的最坏情况
3. 枚举或贪心选择最优连通块

### 复杂度分析

- 时间复杂度：$O(n)$ 每组数据（小规模可枚举）
- 空间复杂度：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, T;
    cin >> c >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        string row1, row2;
        cin >> row1 >> row2;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = row1[i] - '0';
            b[i] = row2[i] - '0';
        }

        int ans = 0;

        if (m >= n) {
            int cnt[4] = {0};
            for (int i = 0; i < n; i++) {
                int t = a[i] * 2 + b[i];
                cnt[t]++;
            }
            ans = 2 * cnt[3] + cnt[1] + cnt[2] - 2 * cnt[0];
            if (ans < 0) ans = 0;
        } else {
            for (int mask = 0; mask < (1 << n); mask++) {
                int bits = 0;
                for (int i = 0; i < n; i++) if (mask >> i & 1) bits++;
                if (bits > m) continue;

                int total = 0;
                for (int i = 0; i < n; i++) {
                    int ta = a[i], tb = b[i];
                    if (mask >> i & 1) {
                        ta = b[i];
                        tb = a[i];
                    }
                    total += ta - tb;
                }
                if (total > ans) ans = total;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
```
