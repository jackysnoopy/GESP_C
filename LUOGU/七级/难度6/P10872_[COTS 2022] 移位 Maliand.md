# [COTS 2022] 移位 Maliand

## 题目描述

给定非负整数 N,K,L，试构造两个 01 序列 S,T，满足：S,T 的长度为 N；S 中恰好有 K 个 1，T 中恰有 L 个 1；f(S,T) 是所有可能的 f(S,T) 中最小的。

## 输入格式

一行三个整数 N,K,L。

## 输出格式

第一行一个整数 F，表示 f(S,T) 的最小值。
接下来两行分别描述序列 S,T。

## 样例

### 样例 1
输入：
```
6 4 3
```
输出：
```
2
011011
101010
```

### 样例 2
输入：
```
5 2 0
```
输出：
```
0
01001
00000
```

## 提示

对于 100% 的数据，1≤N≤5×10^5，0≤K,L≤N。

## 解题思路

### 问题分析
需要构造两个01序列，使得任意循环移位后的按位与之和的最大值最小。

### 核心思路
最小重叠数 = max(0, K + L - N)。

### 算法流程
1. 计算最小重叠数F
2. 构造S和T使得重叠数恰好为F

### 复杂度分析
- 时间复杂度：O(N)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, K, L;
    scanf("%d %d %d", &N, &K, &L);
    
    int F = 0;
    if (K > 0 && L > 0) {
        F = max(0, K + L - N);
    }
    
    printf("%d\n", F);
    
    string S(N, '0');
    for (int i = 0; i < K; i++) {
        S[i] = '1';
    }
    
    string T(N, '0');
    for (int i = 0; i < L; i++) {
        T[i] = '1';
    }
    
    cout << S << endl;
    cout << T << endl;
    
    return 0;
}
```