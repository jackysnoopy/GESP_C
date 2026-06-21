# [GESP202403 五级] B-smooth 数

## 题目描述

小杨同学想寻找一种名为 $ B $-smooth 数的正整数。 

如果一个正整数的最大质因子不超过 $ B $，则该正整数为 $ B $-smooth 数。小杨同学想知道，对于给定的 $ n $ 和 $ B $，有多少个不超过 $ n $ 的 $ B $-smooth 数。

## 输入格式

第一行包含两个正整数 $ n $ 和 $ B $，含义如题面所示。

## 输出格式

输出一个非负整数，表示不超过 $ n $ 的 $ B $-smooth 数的数量。

## 样例

### 样例 #1

**输入**
```
10 3
```

**输出**
```
7
```

## 提示

### 样例解释

在不超过 $10$ 的正整数中，$3$-smooth 数有 ${1,2,3,4,6,8,9}$，共 $7$ 个。

### 数据规模与约定

| 子任务 | 得分 | $n \leq $ | $B$ |
| :-: | :-: | :-: | :-: |
| $1$ | $30$ | $10^3$ | $1 \leq B \leq 10^3$ |
| $2$ | $30$ | $10^6$ | $\sqrt n \leq B \leq 10^6$ |
| $3$ | $40$ | $10^6$ | $1 \leq B \leq 10^6$ | 

对全部的测试数据，保证 $1 \leq n, B \leq 10^6$。

## 解题思路

### 问题分析

$B$-smooth 数的定义：如果一个正整数的最大质因子不超过 $B$，则称该数为 $B$-smooth 数。需要统计不超过 $n$ 的 $B$-smooth 数的数量。

### 核心思路

先求出 $[1,n]$ 中每个数的最大质因子，然后统计那些最大质因子 $\le B$ 的数的个数。使用**埃氏筛**可以高效求出每个数的最小/最大质因子。

### 算法流程

1. 初始化 $max\_prime[1..n] = 0$。
2. 从 $i=2$ 开始遍历到 $n$：如果 $max\_prime[i] == 0$，说明 $i$ 是质数，将其所有倍数 $j$ 的 $max\_prime[j]$ 更新为 $i$。
3. 统计 $[2,n]$ 中 $max\_prime[i] \le B$ 的个数，注意 $1$ 没有质因子，也是 $B$-smooth 数，需要额外加 $1$。

### 复杂度分析

- **时间复杂度：** $O(n \log \log n)$，埃氏筛的复杂度。
- **空间复杂度：** $O(n)$，用于存储最大质因子数组。

### 要点

- $n=1$ 是特例，它的最大质因子为 $0$，肯定 $\le B$，计入答案。
- 如果 $B \ge n$，所有 $[1,n]$ 的数都是 $B$-smooth 数，答案为 $n$。

## 参考代码
## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, B;
    cin >> n >> B;
    vector<int> max_prime(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (max_prime[i] == 0) {
            for (int j = i; j <= n; j += i) {
                max_prime[j] = i;
            }
        }
    }
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        if (max_prime[i] <= B) ans++;
    }
    if (n >= 1) ans++;
    cout << ans << "\n";
    return 0;
}
```
