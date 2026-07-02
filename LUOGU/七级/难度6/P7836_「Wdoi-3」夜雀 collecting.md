# 「Wdoi-3」夜雀 collecting

## 题目描述

米斯蒂娅有一个容量为 v 的背包，有 x 种食材。她会依次经过 n 个采集点，每个采集点有一定量的食材。她可以决定是否开始采集，一旦开始就会全部采集完。每种食材有不同价值，她想让背包中至少有1个的食材的价值和最大。

## 输入格式

第一行三个整数 n,v,x。
第二行 x 个整数，表示每种食材的价值。
接下来 n 行，每行 x 个整数，第 i 行的第 j 个整数表示 Ci,j。

## 输出格式

一行一个整数，表示价值和。

## 样例

### 样例 1
输入：
```
5 3 4
7 11 7 11 
1 0 0 1 
2 1 0 0 
1 1 0 0 
1 0 2 0 
1 0 0 2 
```
输出：
```
29
```

## 提示

对于 100% 的数据，1≤n≤10^6，1≤x≤18，1≤v≤2000，0≤Ci,j，∑j=1xCi,j≤v，0≤Ai≤1000。

## 解题思路

### 问题分析
需要在有限背包容量下，选择采集点采集食材，使得至少有一种食材时价值和最大。

### 核心思路
使用状态压缩DP，状态表示已采集的食材种类。

### 算法流程
1. 定义dp[mask]表示已采集食材种类为mask时的最大价值
2. 对每个采集点，尝试采集并更新状态
3. 考虑背包容量限制

### 复杂度分析
- 时间复杂度：O(n * 2^x)
- 空间复杂度：O(2^x)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1000005;
const int MAXX = 20;
int n, v, x;
int A[MAXX];
int C[MAXN][MAXX];
long long dp[1 << MAXX];

int main() {
    scanf("%d %d %d", &n, &v, &x);
    for (int i = 0; i < x; i++) scanf("%d", &A[i]);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < x; j++) {
            scanf("%d", &C[i][j]);
        }
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        int total = 0;
        for (int j = 0; j < x; j++) total += C[i][j];
        
        for (int mask = (1 << x) - 1; mask >= 0; mask--) {
            if (dp[mask] < 0) continue;
            
            int new_mask = mask;
            int used = 0;
            for (int j = 0; j < x; j++) {
                if (mask & (1 << j)) {
                    used += C[i][j];
                }
            }
            
            if (used + total <= v) {
                new_mask = mask;
                for (int j = 0; j < x; j++) {
                    if (C[i][j] > 0) {
                        new_mask |= (1 << j);
                    }
                }
                long long gain = 0;
                for (int j = 0; j < x; j++) {
                    if (!(mask & (1 << j)) && C[i][j] > 0) {
                        gain += A[j];
                    }
                }
                dp[new_mask] = max(dp[new_mask], dp[mask] + gain);
            }
        }
    }
    
    long long ans = 0;
    for (int mask = 0; mask < (1 << x); mask++) {
        ans = max(ans, dp[mask]);
    }
    
    printf("%lld\n", ans);
    return 0;
}
```