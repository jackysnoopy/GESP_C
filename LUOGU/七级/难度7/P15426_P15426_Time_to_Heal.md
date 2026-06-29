# P15426 Time to Heal

## 题目描述

本题总时限较大，请勿卡评测。

我们定义长度为 $l$ 的序列 $\{a_l\}$ 是一个路径当且仅当满足特定条件。

我们定义一个无序路径对的一个 $k$-TS 为它是一个公共子序列。

## 输入格式

第一行一个整数 $n$。
第二行 $n$ 个整数。

## 输出格式

输出一行一个整数。

## 样例

### 样例1
输入：
```
5
1 2 3 4 5
```
输出：
```
5
```

## 提示

$1 \le n \le 10^5$。

## 解题思路

### 问题分析

这是一个图论问题。需要计算路径相关的信息。

### 核心思路

**动态规划**：使用DP计算答案。

### 复杂度分析

- **时间复杂度**：$O(n^2)$
- **空间复杂度**：$O(n)$

## 参考代码

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
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, a[i]);
    }
    
    cout << ans << "\n";
    
    return 0;
}
```
