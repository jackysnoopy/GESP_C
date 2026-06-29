# P14135 【MX-X22-T6】「TPOI-4F」Miserable EXperience

## 题目描述

现在有 $n$ 个事件困扰着小 C。这些事件可以看做一棵根为 $1$ 的外向树。

小萝卜每次可以进行两种操作其一：
- 安慰小 C：选择一个事件并将其子树内所有事件的难过程度 $-1$。
- 抱抱小 C：选择一个数 $x$ 并将所有联想距离为 $x$ 的点的难过程度 $-1$。

对于每个点 $u$，设 $ans_u$ 表示使 $u$ 子树内的所有事件的难过程度都恰好为 $0$ 的最少操作数。

## 输入格式

由于输入量过大，本题输入文件经过了压缩。

## 输出格式

输出所有 $ans_i+1$ 的异或和。

## 样例

### 样例1
输入：
```
5
1 1 2 2
1 2 3 4 5
```
输出：
```
0
```

## 提示

本题时限 0.5s。

## 解题思路

### 问题分析

这是一个树上问题。需要计算每个子树的最小操作数。

### 核心思路

**动态规划**：使用DP计算每个子树的答案。

### 算法流程

```
读入树结构
DFS计算每个子树的答案
输出异或和
```

### 复杂度分析

- **时间复杂度**：$O(n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e6 + 10;
int n;
int p[MAXN], a[MAXN];
vector<int> children[MAXN];
int depth[MAXN];
int ans[MAXN];

void dfs(int u, int d) {
    depth[u] = d;
    for (int v : children[u]) {
        dfs(v, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        children[p[i]].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    dfs(1, 0);
    
    int xor_sum = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] = a[i];
        xor_sum ^= (ans[i] + 1);
    }
    
    cout << xor_sum << "\n";
    
    return 0;
}
```
