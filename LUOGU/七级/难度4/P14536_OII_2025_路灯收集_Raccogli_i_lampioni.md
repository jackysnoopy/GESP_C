# [OII 2025] 路灯收集 / Raccogli i lampioni

## 题目描述

译自 [Italian Olympiad in Informatics (OII) 2025 - Raccogli i lampioni](https://training.olinfo.it/task/oii_benilluminato)。

OII 纪念碑的建造场地终于被清理干净了！工作人员现在需要考虑的是该区域的照明工作。购买新的路灯是不可能的，因为大部分资金都花在了木材运输上。一个更现实的方案是从乌迪内市借用一些路灯。

乌迪内市有 $N$ 个路口，被 $M$ 条双向道路所连接。在路口 $i(0\le i H, vector A, vector B, vector L);
```

- 整数 $N$：路口的数量。
- 整数 $M$：道路的数量。
- 数组 $H$：下标从 $0$ 到 $N-1$，包含每个路口上路灯的高度。
- 数组 $A,B$ 和 $L$：下标从 $0$ 到 $M-1$，描述了道路，其中第 $j$ 条道路连接路口 $A_{j}$ 和 $B_{j}$，长度为 $L_{j}$ 米。
- 该函数需要返回能借用的最大路灯数量。
- 对于每个测试点，该函数都只会被调用一次。

## 输入格式

评测程序的输入格式如下：

- 第 $1$ 行：两个整数 $N$ 和 $M$。
- 第 $2$ 行：$N$ 个整数 $H_0,H_1,\ldots,H_{N-1}$。
- 第 $2 + j$ 行（$0 \le j < M$）：三个整数 $A_j,B_j,L_j$。

## 输出格式

评测程序的输出格式如下：

输出一行一个整数，表示函数 `illumina` 的返回值。

## 样例

### 样例输入 1
```
4 3
4 2 3 3
0 1 4
0 2 6
0 3 8
```

### 样例输出 1
```
4
```

### 样例输入 2
```
8 10
3 2 3 2 4 6 5 9
0 1 4
1 2 1
2 3 3
3 4 1
0 4 8
2 5 8
3 5 7
1 6 4
5 7 3
6 7 10
```

### 样例输出 2
```
7
```

### 样例输入 3
```
2 2
5 6
0 1 5
0 1 9
```

### 样例输出 3
```
2
```

## 提示

#### 【样例解释】

在样例 1 中，如下的方案可以最大化借用的路灯数量（可以借用所有路灯）：

- 将路灯 $0$ 和路灯 $3$ 放倒在道路 $2$ 上；
- 将路灯 $1$ 放倒在道路 $0$ 上；
- 将路灯 $2$ 放倒在道路 $1$ 上。

在样例 2 中，如下的方案可以最大化借用的路灯数量（不能借用所有的 $8$ 盏路灯，但是可以借用 $7$ 盏）：

- 将路灯 $0$ 和路灯 $4$ 放倒在道路 $4$ 上；
- 将路灯 $1$ 放倒在道路 $0$ 上；
- 将路灯 $2$ 放倒在道路 $5$ 上；
- 将路灯 $3$ 放倒在道路 $2$ 上；
- 将路灯 $5$ 放倒在道路 $6$ 上；
- 将路灯 $6$ 放倒在道路 $9$ 上。

在样例 3 中，如下的方案可以最大化借用的路灯数量（可以借用所有路灯）：

- 将路灯 $0$ 放倒在道路 $0$ 上；
- 将路灯 $1$ 放倒在道路 $1$ 上。

#### 【数据范围】

- $1\le N,M\le 10^6$；
- $1\le H_i\le 1000$；
- $0\le A_j,B_j<N$ 且 $A_j\neq B_j$；
- $1\le L_j\le 2000$。

#### 【子任务】

| 子任务编号 | 分值 | 约束条件 |
| :----: | :--: | :------: |
| $0$ | $0$ | 样例 |
| $1$ | $6$ | $N,M\le 10$ |
| $2$ | $11$ | $M=N-1$，$A_j=j$，$B_j=j+1$ 且 $H_i=1$ |
| $3$ | $16$ | $M=N-1$，$A_j=j$，$B_j=j+1$ |
| $4$ | $27$ | $H_i=1$ 且 $L_j=1$ |
| $5$ | $12$ | $H_i=1$ |
| $6$ | $28$ | 无额外限制 |

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

    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<int> a(m), b(m), l(m);
    for (int i = 0; i < m; i++) cin >> a[i] >> b[i] >> l[i];

    vector<int> road_cap = l;
    int ans = 0;

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return h[x] > h[y];
    });

    for (int i : order) {
        int best_road = -1;
        for (int j = 0; j < m; j++) {
            if ((a[j] == i || b[j] == i) && road_cap[j] >= h[i]) {
                if (best_road == -1 || road_cap[j] > road_cap[best_road]) {
                    best_road = j;
                }
            }
        }
        if (best_road != -1) {
            road_cap[best_road] -= h[i];
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
```
