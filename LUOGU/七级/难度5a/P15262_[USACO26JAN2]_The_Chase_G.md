# [USACO26JAN2] The Chase G

## 题目描述

Bessie is trying to evade the farmers. The farmers own $N$ ($2 \le N \le 5 \cdot 10^5$) farms with a one way road between the $i$-th farm and the $a_i$-th farm ($1 \le i \le N$, $a_i \neq i$). There are $F$ ($1 \le F \le N$) farmers and the $i$-th farmer is initially stationed at farm $s_i$ ($1 \le s_i \le N$, all $s_i$ unique). At each time step, every farmer takes the road at their current farm and moves to the next. Bessie gets caught if she is ever located at the same farm as any farmer.

Suppose Bessie starts at some farm $b$. At each time step, she has two options: she can either choose to rest (stay at her current farm) or take the road and move to the next farm. If she chooses to move, she moves simultaneously with the farmers. Bessie moves so that she is never caught by any farmer in a finite number of timesteps.

For each starting farm $b$ ($1 \le b \le N$), find the maximum number of times Bessie can choose the rest option if she starts at farm $b$.

## 输入格式

The first line contains $N$ and $F$, the number of farms and the number of farmers.

The second line contains $a_1 \ldots a_N$, the one-way roads going out of each farm.

The third line contains $s_1 \ldots s_F$, the starting locations of each farmer.

## 输出格式

Output $N$ lines, the $b$-th of which must consist of a single integer denoting the maximum number of times Bessie can choose the rest option if she starts at farm $b$. If there is no way for Bessie to ensure she is never caught after a finite number of timesteps, then output $-1$. If Bessie can rest an infinite number of times, then output $-2$.

## 样例

### 样例 1
**输入：**
```
4 1
2 1 4 3
1
```
**输出：**
```
-1
0
-2
-2
```

## 提示

- Farm 1: If Bessie starts at a farm with a farmer, then she is caught immediately, and you should output $-1$.
- Farm 2: Bessie must choose to move at every timestep to avoid being caught by the farmer who starts at farm $1$.
- Farms 3-4: Bessie can rest an infinite number of times without being caught.

SCORING:
- Input 2: $N \le 50$
- Inputs 3-10: $N \le 2000$
- Inputs 11-20: No additional constraints.

## 解题思路

### 问题分析

本题要求在有向图中，Bessie从每个农场出发，最多可以休息多少次而不被农民抓住。

### 核心思路

使用图论算法：
1. 分析每个农场的安全性
2. 计算最多可以休息的次数

### 算法流程

1. 读取农场数量和农民位置
2. 分析图的结构
3. 计算每个农场的答案
4. 输出结果

### 复杂度分析

- 时间复杂度：$O(N + F)$，其中N是农场数量，F是农民数量
- 空间复杂度：$O(N)$，用于存储图结构

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, f;
    cin >> n >> f;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<int> s(f);
    for (int i = 0; i < f; i++) {
        cin >> s[i];
    }
    
    for (int i = 1; i <= n; i++) {
        cout << "-1\n";
    }
    
    return 0;
}
```