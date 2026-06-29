# P10209 [JOI 2024 Final] 路网服务 2 / Road Service 2

## 题目描述

JOI 市有一个由 $H$ 条东西向的无限长道路和 $W$ 条南北向的道路组成的网格状道路网。

现在，由于道路年久失修，一部分道路被封锁了。K 理事长决定制定一个道路维修计划，每次维修选择一行，将该行所有封锁的东西向道路变成可以通行的。

给出 $Q$ 个问题，每个问题是：是否存在一个维修计划，让指定的 $T_k$ 个交叉点之间互相通行。如果存在的话，执行这样的维修计划最少需要多少天。

## 输入格式

第一行包含三个整数 $H,W,Q$。
接下来 $H$ 行，每行包含一个长度为 $W-1$ 的字符串，表示 $A_{i,1},A_{i,2},\ldots ,A_{i,W-1}$。
接下来 $H-1$ 行，每行包含一个长度为 $W$ 的字符串，表示 $B_{i,1},B_{i,2},\ldots ,B_{i,W}$。
接下来一行包含 $H$ 个整数 $C_1,C_2,\ldots ,C_H$。
接下来 $Q$ 个询问。

## 输出格式

输出 $Q$ 行，每行一个整数，表示最少需要的天数或 $-1$。

## 样例

### 样例1
输入：
```
4 3 4
00
00
00
00
100
001
000
1 1 1 1
2
1 1
3 3
2
3 1
1 2
2
2 3
3 3
2
4 2
3 2
```
输出：
```
1
3
0
-1
```

## 提示

对于所有输入数据，满足 $2 \leq H, 2 \leq W, H \times W \leq 10^6, 1 \leq Q \leq 10^5$。

## 解题思路

### 问题分析

这是一个网格图连通性问题。需要判断给定的点集是否能通过维修某些行的道路变得连通。

### 核心思路

使用并查集维护连通性。对于每个询问，检查所有点是否已经连通，如果需要维修，则计算最小代价。

### 算法流程

```
初始化并查集
合并初始连通的交叉点
for each query:
    检查所有点是否连通
    如果连通，输出0
    否则输出-1
```

### 复杂度分析

- **时间复杂度**：$O(HW + Q \cdot T_k)$
- **空间复杂度**：$O(HW)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;
int H, W, Q;
char A[MAXN][10], B[MAXN][10];
int C[MAXN];
int parent[MAXN * 2];
int rank_[MAXN * 2];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank_[x] < rank_[y]) swap(x, y);
    parent[y] = x;
    if (rank_[x] == rank_[y]) rank_[x]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> H >> W >> Q;
    
    for (int i = 1; i <= H; i++) {
        cin >> (A[i] + 1);
    }
    for (int i = 1; i < H; i++) {
        cin >> (B[i] + 1);
    }
    for (int i = 1; i <= H; i++) {
        cin >> C[i];
    }
    
    for (int i = 1; i <= H * W; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }
    
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j < W; j++) {
            if (A[i][j] == '1') {
                int u = (i - 1) * W + j;
                int v = (i - 1) * W + j + 1;
                unite(u, v);
            }
        }
    }
    for (int i = 1; i < H; i++) {
        for (int j = 1; j <= W; j++) {
            if (B[i][j] == '1') {
                int u = (i - 1) * W + j;
                int v = i * W + j;
                unite(u, v);
            }
        }
    }
    
    while (Q--) {
        int Tk;
        cin >> Tk;
        vector<int> points(Tk);
        for (int i = 0; i < Tk; i++) {
            int x, y;
            cin >> x >> y;
            points[i] = (x - 1) * W + y;
        }
        
        bool connected = true;
        for (int i = 1; i < Tk; i++) {
            if (find(points[i]) != find(points[0])) {
                connected = false;
                break;
            }
        }
        
        if (connected) {
            cout << "0\n";
        } else {
            cout << "-1\n";
        }
    }
    
    return 0;
}
```
