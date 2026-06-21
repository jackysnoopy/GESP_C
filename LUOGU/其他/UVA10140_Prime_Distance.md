# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/9848cf59ee0ece9e1a0dfd40a08e689a1c5c6604.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/6760a091328104551b134bb6b39accf505df0484.png)

## 样例

### 样例输入
```
2 17
14 17
```

### 样例输出
```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.
```

## 提示



## 解题思路

### 问题分析

给定区间 [L, R]，找其中最近的两个素数和最远的两个相邻素数。L,R 可达 10^9，但 R-L <= 10^6，用区间筛法。

### 核心思路

1. **区间筛法**：用 [2, sqrt(R)] 的素数筛掉 [L, R] 中的合数。
2. 将 [L, R] 映射到数组 offset[i] = i - L。
3. 对每个小素数 p，从 max(p*p, ceil(L/p)*p) 开始筛掉 [L,R] 中 p 的倍数。
4. 遍历筛后的素数，记录相邻素数对的最小/最大间距。

### 算法流程

1. 读入 L, R
2. 线性筛出 [2, sqrt(R)] 的所有素数
3. 区间筛标记 [L, R] 中的合数
4. 遍历素数对，记录最小/最大间距

### 复杂度分析

时间 O((R-L) * log(log(R))) + O(sqrt(R) * log(log(sqrt(R))))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int main() {
    long long L, R;
    while (cin >> L >> R) {
        long long sq = (long long)sqrt((double)R) + 1;
        vector<bool> is_prime(sq + 1, true);
        vector<int> small_primes;
        is_prime[0] = is_prime[1] = false;
        for (long long i = 2; i <= sq; ++i) {
            if (is_prime[i]) {
                small_primes.push_back(i);
                for (long long j = i * i; j <= sq; j += i)
                    is_prime[j] = false;
            }
        }
        long long sz = R - L + 1;
        vector<bool> seg(sz, true);
        if (L == 1) seg[0] = false;
        for (int p : small_primes) {
            long long start = max((long long)p * p, ((L + p - 1) / p) * p);
            for (long long j = start; j <= R; j += p)
                seg[j - L] = false;
        }
        vector<long long> primes;
        for (long long i = L; i <= R; ++i)
            if (seg[i - L]) primes.push_back(i);
        if (primes.size() < 2) {
            cout << "There are no adjacent primes." << endl;
            continue;
        }
        int min_d = INT_MAX, max_d = 0;
        int min_i = 0, max_i = 0;
        for (int i = 1; i < (int)primes.size(); ++i) {
            int d = (int)(primes[i] - primes[i - 1]);
            if (d < min_d) { min_d = d; min_i = i - 1; }
            if (d > max_d) { max_d = d; max_i = i - 1; }
        }
        cout << primes[min_i] << "," << primes[min_i + 1]
             << " are closest, "
             << primes[max_i] << "," << primes[max_i + 1]
             << " are most distant." << endl;
    }
    return 0;
}
```
