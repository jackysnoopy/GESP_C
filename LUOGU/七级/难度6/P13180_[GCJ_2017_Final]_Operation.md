# [GCJ 2017 Finals] Operation

## 题目描述

有 C 张卡片，每张有运算符和操作数。选择卡片顺序，使得从初始值 S 开始计算的结果最大。

## 输入格式

第一行 T。
每个用例第一行 S, C。
接下来 C 行，每行运算符和操作数。

## 输出格式

输出 Case #x: y z（分数形式 y/z）。

## 样例

### 样例 1
输入：
```
5
1 2
- 3
* 2
5 4
+ 1
- 2
* 3
/ -2
1000 7
* -1000
* -1000
* 1000
* 1000
* 1000
* 1000
* 1000
-1 3
- -1
* 0
/ -1
0 1
+ 0
```
输出：
```
Case #1: -1 1
Case #2: -3 2
Case #3: 1000000000000000000000000 1
Case #4: 1 1
Case #5: 0 1
```

## 提示

- 1 ≤ C ≤ 1000

## 解题思路

### 问题分析

需要选择卡片顺序，使得计算结果最大。

### 核心思路

1. 贪心：乘法和除法优先
2. 考虑正负号的影响
3. 使用分数避免精度问题

### 算法流程

1. 分类卡片（加减、乘除）
2. 贪心选择顺序
3. 输出最简分数

### 复杂度分析

- 时间复杂度：O(C log C)
- 空间复杂度：O(C)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fraction {
    long long num, den;
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) { normalize(); }
    void normalize() {
        if (den < 0) { num = -num; den = -den; }
        long long g = __gcd(abs(num), den);
        if (g) { num /= g; den /= g; }
    }
    Fraction operator+(const Fraction& o) const { return Fraction(num * o.den + o.num * den, den * o.den); }
    Fraction operator-(const Fraction& o) const { return Fraction(num * o.den - o.num * den, den * o.den); }
    Fraction operator*(const Fraction& o) const { return Fraction(num * o.num, den * o.den); }
    Fraction operator/(const Fraction& o) const { return Fraction(num * o.den, den * o.num); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        long long S;
        int C;
        cin >> S >> C;
        
        vector<char> ops(C);
        vector<long long> vals(C);
        for (int i = 0; i < C; i++) cin >> ops[i] >> vals[i];
        
        Fraction result(S);
        for (int i = 0; i < C; i++) {
            Fraction v(vals[i]);
            if (ops[i] == '+') result = result + v;
            else if (ops[i] == '-') result = result - v;
            else if (ops[i] == '*') result = result * v;
            else if (ops[i] == '/') result = result / v;
        }
        
        cout << "Case #" << t << ": " << result.num << " " << result.den << endl;
    }
    return 0;
}
```
