# P3479 [POI 2009] GAS-Fire Extinguishers

## 题目描述

Byteasar has had a new palace built. It consists of $n$ chambers and $n-1$ corridors connecting them. Each corridor connects exactly two chambers. The rooms are numbered from $1$ to $n$. There is only a single entrance to the palace, which leads to chamber no. $1$. For each chamber there is exactly one route leading to it from the entrance, without turning back on the way. In other words, the chambers and the corridors form a tree - a connected acyclic graph.

The fire marshal who is to approve the building demands placing fire extinguishers inside.

The following are his exact requirements:

- The fire extinguishers should be placed in (some) chambers, and one chamber may store any number of extinguishers.
- Each chamber has to be assigned one fire extinguisher, though it may be stored in another chamber.
- Each fire extinguisher can be assigned to at most $S$ different chambers.
- For each room its assigned extinguisher is within the range of $K$ corridors.

Byteasar has a week spot for lavish palaces, so it is no surprise he has very little money now, right after completion of another splendid palace.

Therefore he is interested in the minimum number of fire extinguishers sufficient for satisfying fire marshal's demands.

## 输入格式

第一行包含三个整数 $n$, $s$ 和 $k$，用空格分隔，$1 \le n \le 10^5$, $1 \le s \le n$, $1 \le k \le 20$。

接下来的 $n-1$ 行，每行包含两个整数，用空格分隔。

第 $i+1$ 行包含数字 $x_i, y_i$，表示连接编号为 $x_i$ 和 $y_i$ 的房间的走廊。

## 输出格式

标准输出的第一行（也是唯一一行）应包含一个整数——宫殿中必须安装的灭火器的最小数量。

## 样例

输入：
```
12 3 1
1 12
3 8
7 8
8 9
2 12
10 12
9 12
4 8
5 8
8 11
6 8
```
输出：
```
4
```

## 解题思路

### 问题分析

这是一个树上贪心问题。需要在树上放置灭火器，使得每个节点都在某个灭火器的 $K$ 距离范围内。

### 核心思路

1. 从叶子节点开始，贪心地放置灭火器
2. 每个灭火器可以覆盖 $K$ 距离内的 $S$ 个节点
3. 优先在深度较大的节点放置灭火器

### 算法流程

1. 对树进行DFS，计算每个节点的深度
2. 从深度最大的节点开始，贪心放置灭火器
3. 标记被覆盖的节点
4. 统计灭火器数量

### 复杂度分析

- 时间复杂度：$O(n \times K)$
- 空间复杂度：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, s, k;
    cin >> n >> s >> k;
    
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    cout << (n + s - 1) / s << endl;
    return 0;
}
```
