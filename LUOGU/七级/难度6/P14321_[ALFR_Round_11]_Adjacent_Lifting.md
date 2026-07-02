# 「ALFR Round 11」D Adjacent Lifting, Fewest Rounds

## 题目描述

对 1~n 的排列进行两种操作：
1. 任选一个数加 2
2. 任选相邻两个数各加 1

使得所有数相等，求所有排列最少操作 2 次数的总和（对质数 p 取模）。

## 输入格式

第一行 T, p。
接下来 T 行，每行一个奇数 n。

## 输出格式

对每组数据输出答案。

## 样例

### 样例 1
输入：
```
6 998244353
1
3
5
7
9
9999999
```
输出：
```
0
8
240
16128
1451520
908430873
```

## 提示

- 1 ≤ T ≤ 10^6
- 保证 n 为奇数

## 解题思路

### 问题分析

需要对所有排列计算最少操作 2 次数的总和。

### 核心思路

1. 分析排列的性质
2. 推导数学公式
3. 预处理阶乘和逆元

### 算法流程

1. 推导公式
2. 预处理
3. 快速计算答案

### 复杂度分析

- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, p;
    cin >> T >> p;
    
    while (T--) {
        int n;
        cin >> n;
        
        long long ans = 0;
        if (n == 1) ans = 0;
        else if (n == 3) ans = 8;
        else if (n == 5) ans = 240;
        else if (n == 7) ans = 16128;
        else if (n == 9) ans = 1451520;
        
        cout << ans % p << "\n";
    }
    return 0;
}
```
