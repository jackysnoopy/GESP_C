# Matrix Power Series

## 题目描述

给定一个 $n	imes n$ 矩阵 $A$ 和一个正整数 $k$，找出和 $S=A+A^2 +A^3 +...+A^k$。

## 输入格式

输入包含一个测试用例。输入的第一行包含三个正整数 $n$（$n \le 30$）、$k$（$k \le 10^9$）和 $m$（$m < 10^4$）。接下来的 $n$ 行每行包含 $n$ 个小于 $32768$ 的非负整数，按行主序给出 $A$ 的元素。

## 输出格式

以与给定 $A$ 相同的方式输出 $S$ 的元素对 $m$ 取模。

翻译来自于：[ChatGPT](https://chatgpt.com/)

## 样例

### 样例输入
```
2 2 4 
0 1 
1 1
```

### 样例输出
```
1 2
2 3
```

## 提示



## 解题思路

### 问题分析

求 S = A + A^2 + ... + A^k。

### 核心思路

1. 构造分块矩阵 B = [[A, I],[0, I]]，则 B^k = [[A^k, S],[0, I]]（其中 S = A+A^2+...+A^k）。
2. 用矩阵快速幂求 B^k，取左上角 n×n 部分即为 S。

### 算法流程

1. 读入 n, k, 矩阵 A
2. 构造分块矩阵 B
3. 矩阵快速幂 B^k
4. 输出左上角 n×n

### 复杂度分析

时间 O((2n)^3 * log(k))

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1000000007;
struct Mat {
    int n; vector<vector<long long>> a;
    Mat(int n) : n(n), a(n, vector<long long>(n, 0)) {}
};
Mat mul(const Mat &x, const Mat &y) {
    Mat r(x.n);
    for (int i = 0; i < x.n; ++i)
        for (int k = 0; k < x.n; ++k) if (x.a[i][k])
            for (int j = 0; j < x.n; ++j)
                r.a[i][j] = (r.a[i][j] + x.a[i][k] * y.a[k][j]) % MOD;
    return r;
}
Mat power(Mat m, long long e) {
    int n = m.n; Mat r(n);
    for (int i = 0; i < n; ++i) r.a[i][i] = 1;
    while (e > 0) { if (e & 1) r = mul(r, m); m = mul(m, m); e >>= 1; }
    return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long k; cin >> n >> k;
    Mat A(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> A.a[i][j];
    int sz = 2 * n;
    Mat B(sz);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) B.a[i][j] = A.a[i][j];
    for (int i = 0; i < n; ++i) B.a[i][i + n] = 1;
    for (int i = 0; i < n; ++i) B.a[i + n][i + n] = 1;
    B = power(B, k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';
            cout << B.a[i][j + n];
        }
        cout << '\n';
    }
    return 0;
}
```
