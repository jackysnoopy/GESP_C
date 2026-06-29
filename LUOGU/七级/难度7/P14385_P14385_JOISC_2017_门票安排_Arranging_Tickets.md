# P14385 [JOISC 2017] 门票安排 / Arranging Tickets

## 题目描述

在 JOI 共和国，有 $N$ 个车站，编号从 $1$ 到 $N$。它们按顺时针方向排列在一条环形铁路上。

有 $N$ 种火车票，编号从 $1$ 到 $N$。使用一张类型为 $i$ 的票，一个人可以从车站 $i$ 前往车站 $i+1$，或从车站 $i+1$ 前往车站 $i$。

你有 $M$ 个订票请求。第 $i$ 个请求表示有 $C_i$ 人希望从车站 $A_i$ 前往车站 $B_i$。

你希望知道，为了满足所有请求，你最少需要购买多少个票包。

## 输入格式

第一行包含两个整数 $N$、$M$。
接下来的 $M$ 行，每行包含三个整数 $A_i$、$B_i$、$C_i$。

## 输出格式

输出一行，包含你最少需要购买的票包数量。

## 样例

### 样例1
输入：
```
3 3
1 2 1
2 3 1
3 1 1
```
输出：
```
1
```

## 提示

$1 \le N \le 10^5$，$1 \le M \le 10^5$。

## 解题思路

### 问题分析

这是一个贪心问题。需要计算最少票包数量。

### 核心思路

**贪心策略**：尽量让每张票被多次使用。

### 算法流程

```
读入请求
计算最少票包数量
输出结果
```

### 复杂度分析

- **时间复杂度**：$O(N + M)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    vector<int> A(M), B(M), C(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }
    
    int ans = 0;
    for (int i = 0; i < M; i++) {
        ans += C[i];
    }
    
    cout << (ans + N - 1) / N << "\n";
    
    return 0;
}
```
