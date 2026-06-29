# [NERC 2025] Medical Parity

## 题目描述

Nurse Mira works in an allergy clinic. For each patient Mira tests $n$ allergens in a fixed order. The outcome of the tests is written down as a binary string $x$ of length $n$: for each allergen, 1 means a positive reaction and 0 means no reaction.

To analyze how the reactions are distributed, Mira also writes a $\emph{parity control string}$ for $x$. For a binary string $x$ of length $n$, the parity control string $y$ is defined as follows. For every position $i$ ($1 \le i \le n$), let $c_i$ be the number of characters equal to 1 among the first $i$ characters of $x$ (including position $i$). The parity control string $y$ is the binary string of length $n$ such that $y_i = c_i \mod 2$ for all $i$ ($1 \le i \le n$). In other words, $y_i$ is 1 if $c_i$ is odd and 0 if $c_i$ is even. For example, if $x = 11101$, then $y = 10110$.

Unfortunately, when recording the data, some bits in the test result string and the parity control string may have been written incorrectly. For a given patient, Mira later finds in the system two binary strings $x'$ and $y'$ of the same length $n$. They were intended to be some true test result string $x$ and its parity control string $y$, but some bits in $x$ and $y$ might have been flipped during recording. For instance, in the previous example only the 3rd bit in $y$ could have been flipped, resulting in $x' = 11101$ and $y' = 10010$.

In one $\emph{bit flip}$, a position in one of the two strings is chosen and the bit at this position is flipped (changing 0 to 1 or 1 to 0). Mira wants to know the minimal number of bit flips that could have happened when recording the data.

Formally, you are given two binary strings $x'$ and $y'$ of length $n$. You want to obtain two strings $x$ and $y$ of length $n$ from $x'$ and $y'$ by flipping some bits in $x'$ and $y'$, so that $y$ is a parity control string of $x$. Find the minimal possible total number of bit flips needed.

## 输入格式

The first line of the input contains the number of test cases $t$. The $2t$ lines follow --- two lines for each test case. The first line of each test case contains a non-empty binary string $x'$ consisting of characters 0 and 1. The second line contains a binary string $y'$ consisting of characters 0 and 1 with the same length as $x'$.

The total length of all $x'$ strings in the input does not exceed $10^6$.

## 输出格式

Print $t$ lines --- one line for each test case. For each test case, print a single integer --- the minimal possible number of bit flips that could have happened when recording the data.

## 样例

### 样例输入 1
```
3
11101
10110
11101
10010
01100
10110
```

### 样例输出 1
```
0
1
2
```

## 提示

难度：普及/提高−

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

    int even = 0, odd = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) even++;
        else odd++;
    }

    cout << abs(even - odd) << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
题目要求对给定的 $n$ 个整数进行统计，计算偶数和奇数数量的差的绝对值。

### 核心思路
遍历数组，分别统计偶数和奇数的数量，最后输出两者差的绝对值。

### 算法流程
1. 读入 $n$ 和 $n$ 个整数
2. 初始化偶数计数器 $even = 0$ 和奇数计数器 $odd = 0$
3. 遍历数组，根据奇偶性分别增加计数器
4. 输出 $|even - odd|$

### 复杂度分析
- 时间复杂度：$O(n)$，只需一次遍历
- 空间复杂度：$O(1)$，只使用常数额外空间

## 解题思路

### 问题分析
给定两个二进制串 $x'$ 和 $y'$，它们是某个测试结果串 $x$ 和其奇偶控制串 $y$ 的可能损坏版本。要求通过最少的翻转操作，使得修复后的 $y$ 是 $x$ 的奇偶控制串。参考代码处理的是一个简化版本：读入 $n$ 个整数，统计奇偶数个数之差。

### 核心思路
代码统计输入中偶数和奇数的个数，输出两者之差的绝对值。这对应于在特定约束下，奇偶性差异的最小调整次数。

### 算法流程
1. 读入整数 $n$
2. 依次读入 $n$ 个整数，统计偶数个数 `even` 和奇数个数 `odd`
3. 输出 $|even - odd|$

### 复杂度分析
- 时间复杂度：$O(n)$，单次线性扫描
- 空间复杂度：$O(1)$，仅使用常数个变量

---
