# [GKS 2020 #H] Rugby

## 题目描述

On a far away planet, rugby is played in the $2$-dimensional Cartesian coordinate system without bounds. The players can occupy integer grid points only and they can move to the neighboring grid points in any of the $4$ cardinal directions. Specifically, if a player is currently at the point $(X, Y)$, then they can move to either of the points $(X+1, Y)$, $(X-1, Y)$, $(X, Y+1)$, or $(X, Y-1)$ in a single step.

After the game, $N$ players are scattered throughout the coordinate system such that any grid point is empty or occupied by $1$ or more players. They want to gather for a picture and form a perfect horizontal line of $N$ grid points, $1$ player per point, all occupied points next to each other. Formally, the players have to move so as to occupy the grid points $(X, Y)$, $(X+1, Y)$, $(X+2, Y)$, ..., $(X+N-1, Y)$ for some coordinates $X$ and $Y$. What is the minimum total number of steps the players should make to form a perfect line if they are free to choose the position of the line in the coordinate system and the ordering of players is not important?

## 输入格式

The first line of the input gives the number of test cases $T$. $T$ test cases follow. The first line of each test case gives the number of players $N$. The subsequent $N$ lines give the initial coordinates of the players. The $i$-th of these lines contains $2$ integers $X_i$ and $Y_i$, which describe the initial position of the $i$-th player ($1 \le i \le N$).

## 输出格式

For each test case, output one line containing Case $\#x$: $y$, where $x$ is the test case number (starting from $1$) and $y$ is the minimum total number of steps that the players need to make in order to form a perfect horizontal line.

## 样例

### 样例输入 1
```
2
2
1 1
4 4
3
1 1
1 2
1 3
```

### 样例输出 1
```
Case #1: 5
Case #2: 4
```

## 提示

In the $1$st test case, $1$ of many optimal solutions is obtained by the $2$nd player moving $2$ steps to the left and $3$ steps down to the point $(2, 1)$.

In the $2$nd test case, a perfect line can be formed with a total of $4$ steps if the $1$st player moves to the point $(0, 2)$ and the $3$rd player moves to the point $(2, 2)$.

### Limits

**Test Set $1$**

$1 \le N \le 10$.

$-500 \le X_i \le 500$.

$-500 \le Y_i \le 500$.

**Test Set $2$**

$1 \le N \le 10^5$ for at most $10$ cases.

$1 \le N \le 10^4$ for the remaining cases.

$-10^9 \le X_i \le 10^9$.

$-10^9 \le Y_i \le 10^9$.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> scores(n);
    for (int i = 0; i < n; i++) cin >> scores[i];

    int ans = 0;
    for (int s : scores) ans += s;

    cout << ans << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
题目要求将N个分散在坐标系中的玩家移动到一条连续的水平线上，最小化总移动步数。但参考代码实现的是读取数组并计算所有元素的总和。

### 核心思路
参考代码的核心逻辑是读取一个整数数组，遍历数组将所有元素累加，然后输出总和。

### 算法流程
1. 读取玩家数量 n
2. 读取 n 个整数到数组 scores 中
3. 初始化 ans 为 0
4. 遍历数组，将每个元素累加到 ans
5. 输出 ans

### 复杂度分析
- 时间复杂度：O(n)，遍历一次数组
- 空间复杂度：O(n)，存储输入数组
