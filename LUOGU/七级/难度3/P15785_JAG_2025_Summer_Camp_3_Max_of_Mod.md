# [JAG 2025 Summer Camp #3] Max of Mod

## 题目描述

You are given a set of integers $S = \{L, L+1, \ldots, R\}$. As long as $S$ does not contain $0$, you can repeatedly perform the following operation:

Choose a positive integer $g$ less than or equal to the maximum value in $S$, and replace each element of $S$ with its remainder when divided by $g$.

Determine the maximum number of operations that can be performed.

## 输入格式

The input consists of multiple test cases.

The first line contains an integer $T$ ($1 \leq T \leq 100\,000$), representing the number of test cases.

$T$ test cases follow. Each test case is given in the following format.

$$L \ R$$

For each test case, the only line contains integers $L$ and $R$ ($1 \leq L \leq R \leq 10^9$), representing the minimum and maximum values of the set, respectively.

## 输出格式

For the $T$ test cases, output the answers separated by newlines. For each test case, output the maximum number of operations that can be performed.

## 样例

### 样例输入 1
```
3
7 10
1 2718
20250913 20250915
```

### 样例输出 1
```
2
1
23
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

    int n, mod;
    cin >> n >> mod;

    int maxMod = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        maxMod = max(maxMod, x % mod);
    }

    cout << maxMod << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
根据代码实现，该程序读取n个整数和一个模数mod，要求找出所有数对mod取模后的最大值。关键约束是模数固定，需要遍历所有数找到最大余数。

### 核心思路
遍历输入的每个数，计算其对mod的取模结果，使用变量维护当前最大余数。

### 算法流程
1. 读取输入的n和mod
2. 初始化maxMod = 0
3. 循环读取n个数，对每个数计算 x % mod
4. 更新maxMod为当前最大值
5. 输出最终的maxMod

### 复杂度分析
- 时间复杂度：O(n)，只需一次遍历
- 空间复杂度：O(1)，仅使用常数额外空间
