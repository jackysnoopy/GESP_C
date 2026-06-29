# [GCJ 2015 #1B] Noisy Neighbors

## 题目描述

You are a landlord who owns a building that is an $R \times C$ grid of apartments; each apartment is a unit square cell with four walls. You want to rent out $N$ of these apartments to tenants, with exactly one tenant per apartment, and leave the others empty. Unfortunately, all of your potential tenants are noisy, so whenever any two occupied apartments share a wall (and not just a corner), this will add one point of unhappiness to the building. For example, a $2 \times 2$ building in which every apartment is occupied has four walls that are shared by neighboring tenants, and so the building's unhappiness score is $4$.

If you place your $N$ tenants optimally, what is the minimum unhappiness value for your building?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow; each contains three space-separated integers: $R$, $C$, and $N$.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is the minimum possible unhappiness for the building.

## 样例

### 样例输入 1
```
4
2 3 6
4 1 2
3 3 8
5 2 0
```

### 样例输出 1
```
Case #1: 7
Case #2: 0
Case #3: 8
Case #4: 0
```

## 提示

**Sample Explanation**

In Case #1, every room is occupied by a tenant and all seven internal walls have tenants on either side.

In Case #2, there are various ways to place the two tenants so that they do not share a wall. One is illustrated below.

In Case #3, the optimal strategy is to place the eight tenants in a ring, leaving the middle apartment unoccupied.

Here are illustrations of sample cases 1-3. Each red wall adds a point of unhappiness.

![](https://cdn.luogu.com.cn/upload/image_hosting/sivst9rm.png)

**Sample Explanation**

- $1 \leq T \leq 1000$.
- $0 \leq N \leq R \times C$.

**Small dataset(12 Pts)**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq R \times C \leq 16$.

**Large dataset(15 Pts)**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq R \times C \leq 10000$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int R, C, N;
        cin >> R >> C >> N;

        int total = R * C;
        if (N == 0 || N == total) {
            cout << "Case #" << t << ": " << (N == total ? (R-1)*C + R*(C-1) : 0) << "\n";
            continue;
        }

        int half = (total + 1) / 2;
        if (N <= half) {
            cout << "Case #" << t << ": 0\n";
        } else {
            int extra = N - half;
            int ans = 0;

            if (R == 1 || C == 1) {
                ans = extra;
            } else {
                ans = min(extra, 2 * extra - (R > 1 && C > 1 ? 1 : 0));
            }

            cout << "Case #" << t << ": " << ans << "\n";
        }
    }

    return 0;
}
```

## 解题思路

### 问题分析
在 R×C 的网格中放置 N 个租户，使得相邻（共享墙壁）的租户对数最少，即不快乐值最小。

### 核心思路
利用棋盘染色思想：将网格按黑白交替染色，优先放置在数量较多的颜色上（占总格数的 ⌈(R×C)/2⌉ 个位置）。若 N 不超过该数量，不快乐值为 0；否则需计算额外放置带来的不快乐值。

### 算法流程
1. 计算总数 total = R × C
2. 若 N = 0，不快乐值为 0；若 N = total，不快乐值为所有内部墙壁数
3. 计算 half = ⌈total/2⌉，即棋盘染色中较多颜色的格子数
4. 若 N ≤ half，不快乐值为 0（可全部放在同色格子上）
5. 若 N > half，计算 extra = N - half：
   - 对于一维情况（R=1 或 C=1）：不快乐值 = extra
   - 对于二维情况：不快乐值 = min(extra, 2×extra - 1)

### 复杂度分析
- 时间复杂度：O(1)，直接数学计算
- 空间复杂度：O(1)
