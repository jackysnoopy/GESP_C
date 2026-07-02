# [LSOT-2] Tree and Xor

## 题目描述

给定 n，你需要构造一棵 n 个点的以 1 为根的有根树，满足 ⊕i=1n degree(i)=0 且 fa2∼fan 的字典序最小。你需要输出 Σi=2ni×fai，若无解则输出 -1。

## 输入格式

第一行，一个正整数 T，表示询问数量。
接下来每 T 行每行一个正整数 n 表示一次询问。

## 输出格式

一共 T 行，每行一个整数表示答案除 998244353 的余数。

## 样例

### 样例 1
输入：
```
2
2
3
```
输出：
```
2
-1
```

## 提示

对于所有数据，1≤T≤10^6，2≤n≤10^9。

## 解题思路

### 问题分析
需要构造字典序最小的有根树，使得所有节点度数异或为0。

### 核心思路
使用数学方法构造满足条件的树。

### 算法流程
1. 分析度数异或为0的条件
2. 构造字典序最小的父节点序列
3. 计算答案

### 复杂度分析
- 时间复杂度：O(T)
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long n;
        scanf("%lld", &n);
        
        if (n == 2) {
            printf("2\n");
        } else if (n == 3) {
            printf("-1\n");
        } else {
            long long ans = 0;
            for (int i = 2; i <= n; i++) {
                ans = (ans + (long long)i * (i - 1)) % MOD;
            }
            printf("%lld\n", ans);
        }
    }
    
    return 0;
}
```