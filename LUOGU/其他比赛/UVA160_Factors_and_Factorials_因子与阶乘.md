# UVA160 - Factors and Factorials (因子与阶乘)

## 题目描述

给定 n，计算 n! 的质因数分解。n! 表示 1 到 n 的乘积。

## 输入格式

每行一个整数 n（2 ≤ n ≤ 100），以 `0` 结尾。

## 输出格式

格式化输出 n! 的质因数分解，每行最多15个指数。

## 样例

输入：
```
25
30
0
```

输出：
```
 25! = 22 10  7  4  2  1  1  1  0  0  0  0  0  0  0
 30! = 26 14  8  6  4  3  2  1  1  1  0  0  0  0  0
```

## 提示

- 输出格式要求每行15个质数的指数，不足15个用0填充
- 右对齐，宽度为3

## 解题思路

### 问题分析

n! 的质因数分解等价于统计每个质数 p 在 2, 3, ..., n 中出现的总次数。

### 核心思路

1. 预处理100以内的所有质数
2. 对每个数 i (2 ≤ i ≤ n)，分解质因数并累加
3. 格式化输出

### 算法流程

1. 用筛法预处理质数表
2. 对 2 到 n 的每个数进行质因数分解
3. 统计每个质数的指数
4. 按格式输出

### 复杂度分析

- 时间复杂度：O(N * π(N))，π(N)为不超过N的质数个数
- 空间复杂度：O(π(N))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100;
vector<int> primes;
bool isPrime[MAXN + 1];

void sieve() {
    fill(isPrime, isPrime + MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    sieve();
    int n;
    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << "\n";
        first = false;
        vector<int> cnt(primes.size(), 0);
        for (int i = 2; i <= n; i++) {
            int tmp = i;
            for (int j = 0; j < (int)primes.size() && primes[j] <= tmp; j++) {
                while (tmp % primes[j] == 0) {
                    cnt[j]++;
                    tmp /= primes[j];
                }
            }
        }
        printf("%3d! =", n);
        int line = 0;
        for (int i = 0; i < (int)primes.size() && primes[i] <= n; i++) {
            if (line == 15) {
                printf("\n      ");
                line = 0;
            }
            printf("%3d", cnt[i]);
            line++;
        }
        printf("\n");
    }
    return 0;
}
```
