# [Poetize6] IncDec Sequence

## 题目描述
给定一个长度为 $n$ 的数列 ${a_1,a_2,\cdots,a_n}$，每次可以选择一个区间 $[l,r]$，使这个区间内的数都加 $1$ 或者都减 $1$。 

请问至少需要多少次操作才能使数列中的所有数都一样，并求出在保证最少次数的前提下，最终得到的数列有多少种。

## 输入格式
第一行一个正整数 $n$。  
接下来 $n$ 行，每行一个整数，第 $i+1$ 行的整数表示 $a_i$。

## 输出格式
第一行输出最少操作次数。  
第二行输出最终能得到多少种结果。

## 样例
**样例 1**
- 输入：
```
4
1
1
2
2
```
- 输出：
```
1
2
```

## 提示
对于 $100\%$ 的数据，$n\le 100000$，$0 \le a_i \le 2^{31}$。

## 解题思路

### 问题分析
需要通过区间加减操作使数列所有元素相等。每次操作可以对一个区间 $[l,r]$ 内的所有元素加 1 或减 1。

### 核心思路
使用差分数组。设 $d_i = a_i - a_{i-1}$（$i \geq 2$），$d_1 = a_1$。一次操作 $[l,r]$ 加 1 相当于 $d_l$ 加 1，$d_{r+1}$ 减 1（如果 $r+1 \leq n$）。要使所有数相等，需要 $d_2 = d_3 = \cdots = d_n = 0$。

### 算法流程
1. 计算差分数组 $d_i = a_i - a_{i-1}$（$i \geq 2$）
2. 将正数和负数分别求和，得到 $pos$ 和 $neg$
3. 最少操作次数为 $\max(pos, neg)$
4. 最终结果的种数为 $|pos - neg| + 1$

### 复杂度分析
- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long pos = 0, neg = 0;
    for (int i = 1; i < n; i++) {
        long long d = a[i] - a[i-1];
        if (d > 0) pos += d;
        else neg -= d;
    }
    cout << max(pos, neg) << "\n" << abs(pos - neg) + 1 << "\n";
    return 0;
}
```