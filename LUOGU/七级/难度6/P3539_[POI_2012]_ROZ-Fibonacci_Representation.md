# P3539 [POI 2012] ROZ-Fibonacci Representation

## 题目描述

斐波那契数列是一个整数序列，称为斐波那契数，定义如下：

$Fib_0 = 0, Fib_1 = 1, Fib_n = Fib_{n-2} + Fib_{n-1} \text{ for } n > 1$

其初始元素为：0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...

Byteasar正在研究将数字表示为斐波那契数的和或差。目前他想知道对于给定的正整数 $k$，什么是最小表示，即使用最少数量（不一定不同）的斐波那契数来表示 $k$。

例如，数字10、19、17和1070可以分别使用2、2、3和4个斐波那契数最小表示如下：

$10 = 5 + 5$

$19 = 21 - 2$

$17 = 13 + 5 - 1$

$1070 = 987 + 89 - 5 - 1$

帮助Byteasar！编写一个程序，对于给定的正整数 $k$，确定将其表示为斐波那契数的和或差所需的最少斐波那契数数量。

## 输入格式

第一行一个正整数 $p$（$1 \le p \le 10$），表示查询数量。接下来 $p$ 行，每行一个正整数 $k$（$1 \le k \le 1 \times 10^{17}$）。

## 输出格式

对于每个查询，程序应在标准输出上打印将数字 $k$ 表示为斐波那契数的和或差所需的最少斐波那契数数量。

## 样例

输入：
```
1
1070
```
输出：
```
4
```

## 解题思路

### 问题分析

这是一个经典的斐波那契贪心问题，利用Zeckendorf定理。

### 核心思路

1. 预处理斐波那契数列
2. 对于每个查询，从大到小贪心选取斐波那契数
3. 利用斐波那契数的性质，可以证明贪心策略是最优的

### 算法流程

1. 预处理斐波那契数列直到超过 $10^{17}$
2. 对于每个查询 $k$：
   - 从大到小遍历斐波那契数
   - 如果当前斐波那契数不超过 $k$，则选取它并从 $k$ 中减去
   - 统计选取的斐波那契数数量

### 复杂度分析

- 时间复杂度：$O(p \times \log k)$
- 空间复杂度：$O(\log k)$

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
    
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(2);
    while (fib.back() < 1e17) {
        fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
    }
    
    int p;
    cin >> p;
    while (p--) {
        long long k;
        cin >> k;
        
        int ans = 0;
        for (int i = fib.size() - 1; i >= 0 && k > 0; i--) {
            if (k >= fib[i]) {
                k -= fib[i];
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```
