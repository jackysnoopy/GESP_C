# P11983 [JOIST 2025] 展览会 3 / Exhibition 3

## 题目描述

JOI 美术馆计划近期举办一场绘画展览。馆方拥有编号为 $1$ 至 $N$ 的 $N$ 幅画作，其中画作 $i$ 的**美观值**为 $A_i$。

共有 $M$ 家杂志将对展览进行报道。杂志 $j$ 将发布排列中从左数第 $L_j, L_j + 1, \ldots, R_j$ 幅画作的照片。杂志 $j$ 报道的**吸引力**定义为该杂志所覆盖画作的最大美观值。

JOI 君希望排列画作，使得序列 $b = (b_1, b_2, \ldots, b_M)$ 的字典序最大化。

## 输入格式

$N$ $M$
$A_1$ $A_2$ $\cdots$ $A_n$
$L_1$ $R_1$
$L_2$ $R_2$
$\vdots$
$L_M$ $R_M$

## 输出格式

输出 $M$ 行，第 $i$ 行的正整数为 $b_i$。

## 样例

### 样例1
输入：
```
4 4
1 2 1 2
1 2
2 3
3 4
1 4
```
输出：
```
2
2
1
2
```

## 提示

- $1 ≤ N ≤ 10^5$；
- $1 ≤ M ≤ 10^5$；
- $1 ≤ A_i ≤ N$；
- $1 ≤ L_j ≤ R_j ≤ N$。

## 解题思路

### 问题分析

这是一个贪心问题。需要排列画作，使得杂志报道的吸引力字典序最大。

### 核心思路

**贪心策略**：按影响力从大到小处理杂志，每次选择覆盖区间内的最大美观值。

### 算法流程

```
按影响力从大到小处理杂志
对于每个杂志:
    找到覆盖区间内的最大美观值
    标记使用过的画作
输出结果
```

### 复杂度分析

- **时间复杂度**：$O(M \cdot N)$（暴力）
- **空间复杂度**：$O(N + M)$

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
    
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    vector<int> L(M), R(M);
    for (int i = 0; i < M; i++) {
        cin >> L[i] >> R[i];
        L[i]--;
        R[i]--;
    }
    
    vector<int> order(M);
    for (int i = 0; i < M; i++) order[i] = i;
    
    vector<int> result(M);
    vector<bool> used(N, false);
    
    for (int idx = 0; idx < M; idx++) {
        int j = order[idx];
        
        int max_val = 0;
        for (int k = L[j]; k <= R[j]; k++) {
            if (!used[k]) {
                max_val = max(max_val, A[k]);
            }
        }
        
        result[j] = max_val;
        
        for (int k = L[j]; k <= R[j]; k++) {
            if (A[k] == max_val && !used[k]) {
                used[k] = true;
                break;
            }
        }
    }
    
    for (int i = 0; i < M; i++) {
        cout << result[i] << "\n";
    }
    
    return 0;
}
```
