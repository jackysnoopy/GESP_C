# [POI 2007] ZAP-Queries

## 题目描述

密码学家正在尝试破解一种叫 BSA 的密码。

他发现，在破解一条消息的同时，他还需要回答这样一种问题：

给出 `a,b,d`，求满足 `1 \leq x \leq a`，`1 \leq y \leq b`，且 `\gcd(x,y)=d` 的二元组 `(x,y)` 的数量。

因为要解决的问题实在太多了，他便过来寻求你的帮助。

## 输入格式

输入第一行一个整数 `n`，代表要回答的问题个数。

接下来 `n` 行，每行三个整数 `a,b,d`。

## 输出格式

对于每组询问，输出一个整数代表答案。

## 样例

### 样例输入
```
2
4 5 2
6 4 3
```

### 样例输出
```
3
2
```

## 提示

#### 数据规模与约定

对于全部的测试点，保证 `1 \leq n \leq 5 	imes 10^4`，`1 \leq d \leq a,b \leq 5 	imes 10^4`。

## 解题思路

### 问题分析

求满足 1<=x<=a, 1<=y<=b, gcd(x,y)=d 的二元组数量。

### 核心思路

1. 转化：求 gcd(x,y)=d 等价于 gcd(x/d, y/d)=1。
2. 令 a'=a/d, b'=b/d，求 sum(mu(k)*floor(a'/k)*floor(b'/k))。
3. **莫比乌斯反演 + 数论分块**：对 floor(a'/k) 和 floor(b'/k) 相同的 k 分块求和。

### 算法流程

1. 预处理莫比乌斯函数
2. 对每组询问，数论分块求和
3. 输出答案

### 复杂度分析

时间 O(sqrt(max(a,b)))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 50001;
int mu[MAXN], primes[MAXN], pcnt = 0;
bool is_comp[MAXN];

void init() {
    mu[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        if (!is_comp[i]) { primes[pcnt++] = i; mu[i] = -1; }
        for (int j = 0; j < pcnt && i * primes[j] < MAXN; ++j) {
            is_comp[i * primes[j]] = true;
            if (i % primes[j] == 0) { mu[i * primes[j]] = 0; break; }
            mu[i * primes[j]] = -mu[i];
        }
    }
}

long long solve(int a, int b) {
    long long res = 0;
    int m = min(a, b);
    for (int l = 1, r; l <= m; l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        res += (long long)(a / l) * (b / l) * (mu[r] - mu[l - 1]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    for (int i = 1; i < MAXN; ++i) mu[i] += mu[i - 1];
    int T;
    cin >> T;
    while (T--) {
        int a, b, d;
        cin >> a >> b >> d;
        a /= d; b /= d;
        cout << solve(a, b) << '\n';
    }
    return 0;
}
```
