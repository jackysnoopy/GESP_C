# [GCJ 2010 Finals] Candy Store

## 题目描述

最多 k 个顾客，每人购买 1..C 克糖果。每天订购整数克数的盒子，确保无论顾客买多少都能满足。求最少盒子数。

## 输入格式

第一行 T，每组包含 k 和 C。

## 输出格式

Case #x: y，y 为最少盒子数。

## 样例

```
4
1 5
2 2
10 3
2 50
```

输出：
```
Case #1: 3
Case #2: 3
Case #3: 19
Case #4: 11
```

## 解题思路

### 问题分析
需要预先订购盒子，使得无论 k 个顾客分别买多少（各 1..C），都能用已订购的盒子凑出。

### 核心思路
- k=1 时：用二进制表示，需要 ceil(log2(C+1)) 个盒子
- k≥2 时：需要额外盒子应对前一个顾客用掉部分盒子的情况

### 算法流程
1. 计算二进制位数
2. 根据 k 和 C 计算最少盒子

### 复杂度分析
- 时间：O(log C)
- 空间：O(1)

## 参考代码

```cpp
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t=1; t<=T; t++) {
        long long k, C; cin >> k >> C;
        cout << "Case #" << t << ": ";
        if (k==1) {
            long long ans=0, sum=1;
            while (sum<=C) { ans++; sum*=2; }
            cout<<ans<<"\n";
        } else {
            long long bits=0, sum=1;
            while (sum<=C) { bits++; sum*=2; }
            cout<<bits*k+1<<"\n";
        }
    }
    return 0;
}
```
