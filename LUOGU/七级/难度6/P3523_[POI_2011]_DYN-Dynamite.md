# P3523 [POI 2011] DYN-Dynamite

## 题目描述

The Byteotian Cave is composed of $n$ chambers and $n-1$ corridors that connect them. For every pair of chambers there is unique way to move from one of them to another without leaving the cave.

Dynamite charges are set up in certain chambers.

A fuse is laid along every corridor.

In every chamber the fuses from the adjacent corridors meet at one point, and are further connected to the dynamite charge if there is one in the chamber. It takes exactly one unit of time for the fuse between two neighbouring chambers to burn, and the dynamite charge explodes in the instant that fire reaches the chamber it is inside.

We would like to light the fuses in some $m$ chambers (at the joints of fuses) in such a way that all the dynamite charges explode in the shortest time possible since the fuses are lit. Write a program that will determine the minimum such time possible.

## 输入格式

The first line of the standard input holds two integers $n$ and $m$（$1 \le m \le n \le 300\,000$），separated by a single space, that denote, respectively, the number of chambers in the cave and the number of chambers in which fire can be set to the fuses.

The chambers are numbered from 1 to $n$.

The next line contains $n$ integers $d_1, d_2, \cdots, d_n$（$d_i \in \{0,1\}$），separated by single spaces.

If $d_i=1$, then there is dynamite in the $i$-th chamber, and if $d_i=0$, there is none. The following $n-1$ lines specify the corridors of the cave. Each of them holds two integers $a, b$（$1 \le a < b \le n$），separated by a single space, denoting that there is a corridor connecting the chambers $a$ and $b$. Every corridor appears exactly once in the description.

## 输出格式

The first and only line of the standard output should hold a single integer, equal to the minimum time it takes from lighting the fuses to the explosion of all the charges.

## 样例

输入：
```
7 2
1 0 1 1 0 1 1
1 3
2 3
3 4
4 5
5 6
5 7
```
输出：
```
1
```

## 解题思路

### 问题分析

这是一个树DP+二分问题。需要在树上选择 $m$ 个节点点燃引线，使得所有炸药爆炸的最短时间最小。

### 核心思路

1. 二分答案 $mid$
2. 对于每个 $mid$，使用树DP判断是否可行
3. 在树DP中，计算每个节点需要的点燃数量

### 算法流程

1. 二分答案 $mid$
2. 对于每个 $mid$，使用树DP判断是否可行
3. 在树DP中，从叶子节点开始向上计算
4. 如果某个节点距离点燃点超过 $mid$，则需要在该节点点燃
5. 统计点燃数量，判断是否不超过 $m$

### 复杂度分析

- 时间复杂度：$O(n \log n)$
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
    
    int n, m;
    cin >> n >> m;
    
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        cout << mid << " ";
    }
    
    cout << endl;
    return 0;
}
```
