# [JRKSJ ExR] 淇宝的划分

## 题目描述

淇宝有一个由正整数构成的大小为 n 的可重集 A，他想把这个可重集划分成两部分 S,T。求所有划分方案中，|(gcd of S)-(lcm of T)| 的最小值。

## 输入格式

第一行一个正整数 T 表示测试数据组数。
对于每组测试数据：
第一行一个正整数 n。
第二行 n 个正整数 a1~an。

## 输出格式

对于每组测试数据，输出一行，一个非负整数。

## 样例

### 样例 1
输入：
```
3
4
1 2 3 4
5
3 3 4 5 5
6
4 6 12 13 26 39
```
输出：
```
0
2
1
```

## 提示

对于 100% 的数据，1≤T≤10^4，2≤n≤10^6，Σn≤5×10^6，1≤ai≤10^18。

## 解题思路

### 问题分析
需要将可重集划分为两部分，使得GCD和LCM的差值最小。

### 核心思路
尝试不同的划分方式，计算GCD和LCM的差值。

### 算法流程
1. 枚举所有可能的划分
2. 计算每种划分的GCD和LCM
3. 取最小差值

### 复杂度分析
- 时间复杂度：O(T * n * 2^n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n;
        scanf("%d", &n);
        
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        
        long long min_val = *min_element(a.begin(), a.end());
        
        long long gcd_val = a[0];
        for (int i = 1; i < n; i++) {
            gcd_val = __gcd(gcd_val, a[i]);
        }
        
        long long lcm_val = a[n-1];
        for (int i = n-2; i >= 0; i--) {
            lcm_val = lcm_val / __gcd(lcm_val, a[i]) * a[i];
        }
        
        printf("%lld\n", abs(gcd_val - lcm_val));
    }
    
    return 0;
}
```