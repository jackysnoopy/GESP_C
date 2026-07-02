# UVA113 - Powers of Phis (斐波那契幂)

## 题目描述

计算黄金比例 φ = (1+√5)/2 的 n 次幂，四舍五入到最近的整数。

## 输入格式

多行输入，每行包含一个整数 n (1 ≤ n ≤ 2147483647)。

## 输出格式

输出 φ^n 四舍五入到最近的整数。

## 样例

输入：
```
1
2
3
```

输出：
```
2
3
4
```

## 解题思路

### 问题分析

黄金比例 φ = (1+√5)/2 ≈ 1.618，需要计算 φ^n 的值。由于 n 可能非常大（最大到 2^31-1），直接计算浮点数幂会导致精度问题。

### 核心思路

利用斐波那契数列与黄金比例的闭合公式关系：

φ^n = F(n) * φ + F(n-1)

其中 F(n) 是第 n 个斐波那契数。这个公式可以通过数学归纳法证明。

对于大数 n，可以使用矩阵快速幂来高效计算斐波那契数。

### 算法流程

1. 读取输入的 n
2. 使用矩阵快速幂计算 F(n) 和 F(n-1)
3. 利用公式 φ^n = F(n) * φ + F(n-1) 计算结果
4. 四舍五入输出

### 复杂度分析

- 时间复杂度：O(log n)，矩阵快速幂的时间复杂度
- 空间复杂度：O(1)，只需要常数空间

## 参考代码

```cpp
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;

struct Matrix {
    ll mat[2][2];
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = 1;
        mat[1][1] = 0;
    }
    Matrix(ll a, ll b, ll c, ll d) {
        mat[0][0] = a; mat[0][1] = b;
        mat[1][0] = c; mat[1][1] = d;
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix result(0, 0, 0, 0);
    result.mat[0][0] = a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0];
    result.mat[0][1] = a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1];
    result.mat[1][0] = a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0];
    result.mat[1][1] = a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1];
    return result;
}

Matrix matrixPower(Matrix base, ll exp) {
    Matrix result(1, 0, 0, 1);
    while (exp > 0) {
        if (exp & 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    while (cin >> n) {
        if (n == 1) {
            cout << "2\n";
            continue;
        }
        
        Matrix base;
        Matrix result = matrixPower(base, n);
        
        ll fn = result.mat[0][0];
        ll fn1 = result.mat[0][1];
        
        double phi = (1.0 + sqrt(5.0)) / 2.0;
        double ans = fn * phi + fn1;
        
        cout << (ll)round(ans) << "\n";
    }
    
    return 0;
}
```
