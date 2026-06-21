# [GESP202412 四级] Recamán

## 题目描述

小杨最近发现了有趣的 Recamán 数列，这个数列是这样生成的：

- 数列的第一项 $a_1$ 是 $1$；
- 如果 $a_{k-1}-k$ 是正整数并且没有在数列中出现过，那么数列的第 $k$ 项 $a_k$ 为 $a_{k-1}-k$，否则为 $a_{k-1}+k$。

小杨想知道 Recamán 数列的前 $n$ 项从小到大排序后的结果。手动计算非常困难，小杨希望你能帮他解决这个问题。

## 输入格式

第一行，一个正整数 $n$。

## 输出格式

一行，$n$ 个空格分隔的整数，表示 Recamán 数列的前 $n$ 项从小到大排序后的结果。

## 样例

### 样例 #1

**输入**
```
5
```
**输出**
```
1 2 3 6 7
```

### 样例 #2

**输入**
```
8
```
**输出**
```
1 2 3 6 7 12 13 20
```

## 解题思路

### 问题分析

模拟生成 Recamán 数列的前 $n$ 项，然后排序输出。

生成规则：
- $a_1 = 1$
- 对于 $k = 2, 3, \dots, n$：
  - 如果 $a_{k-1} - k > 0$ 且该数未在之前出现过，则 $a_k = a_{k-1} - k$
  - 否则 $a_k = a_{k-1} + k$

### 核心思路

用一个数组 $a$ 存储数列，用一个布尔数组或集合记录哪些数已经出现过。按规则递推生成每一项，最后对整个数组排序输出。

### 算法流程

1. 读取 $n$。
2. 初始化 $a[1] = 1$，标记 $1$ 已出现。
3. 从 $k = 2$ 遍历到 $n$：
   - 计算 $\text{candidate} = a[k-1] - k$。
   - 如果 $\text{candidate} > 0$ 且未出现过，则 $a[k] = \text{candidate}$。
   - 否则 $a[k] = a[k-1] + k$。
   - 标记 $a[k]$ 已出现。
4. 对数组 $a[1..n]$ 排序。
5. 输出排序后的结果。

### 复杂度分析

- **时间复杂度：** $O(n \log n)$，主要来自排序。$n \le 3000$，完全可行。
- **空间复杂度：** $O(n + M)$，其中 $M$ 为出现数的范围。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_set<int> seen;
    a[0] = 1;
    seen.insert(1);
    for (int k = 2; k <= n; k++) {
        int cand = a[k - 2] - k;
        if (cand > 0 && !seen.count(cand)) {
            a[k - 1] = cand;
        } else {
            a[k - 1] = a[k - 2] + k;
        }
        seen.insert(a[k - 1]);
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    return 0;
}
```
