# P11880 [RMI 2024] 选区间 / Choose Interval

## 题目描述

有一个**无限长**的数列 $A$，初始时 $A$ 中元素全为 $0$。

给定 $n$ 个区间 $[l_i,r_i]$，对于 $i=1,2,\ldots,n$，你需要执行以下的**一种**操作恰好一次：
1. $\forall j\in [l_i,r_i]$，令 $A_j\gets A_j+1$。
2. $\forall j \in \mathbb Z \land j\not\in [l_i,r_i]$，令 $A_j\gets A_j+1$。

构造一组方案，使得操作完后数列中最大值最小。

## 输入格式

第一行，一个正整数 $n$。
接下来 $n$ 行，第 $i$ 行两个正整数 $l_i,r_i$。

## 输出格式

第一行，一个正整数，表示最小化的最大值。
第二行输出一个长度为 $n$ 的 $\texttt{01}$ 串 $s$。

## 样例

### 样例1
输入：
```
5
1 3
2 4
1 2
3 5
2 3
```
输出：
```
2
11011
```

## 提示

对于 $100\%$ 的数据，保证 $1\le n\le 2\times 10^5$，$1\le l_i\le r_i\le 2n$。

## 解题思路

### 问题分析

这是一个贪心问题。需要为每个区间选择操作，使得最终数列最大值最小。

### 核心思路

**贪心策略**：尽量选择操作使得重叠区域最小。

### 算法流程

```
对于每个区间:
    计算选择两种操作后的最大值
    选择使最大值较小的操作
输出答案
```

### 复杂度分析

- **时间复杂度**：$O(n^2)$（暴力）
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    
    string ans(n, '0');
    int max_val = 0;
    
    vector<int> cnt(2 * n + 2, 0);
    for (int i = 0; i < n; i++) {
        if (ans[i] == '1') {
            cnt[l[i]]++;
            cnt[r[i] + 1]--;
        } else {
            cnt[1]++;
            cnt[l[i]]--;
            cnt[r[i] + 1]++;
        }
    }
    
    int cur = 0;
    for (int i = 1; i <= 2 * n; i++) {
        cur += cnt[i];
        max_val = max(max_val, cur);
    }
    
    cout << max_val << "\n";
    cout << ans << "\n";
    
    return 0;
}
```
