# [JOI Open 2019] 三级跳 / Triple Jump

## 题目描述

有一条路，包含 N 段，编号 1~N。第 i 段有一个强度 Ai。JOI 君准备进行 Q 次三段跳，每次需要在区间 [Lj,Rj] 中选择三个位置 a<b<c，满足 b-a≤c-b，求强度和的最大值。

## 输入格式

第 1 行 1 个整数 N。
第 2 行 N 个整数，代表 A1,A2,...,An。
第 3 行 1 个整数 Q。
第 4~4+Q-1 行，每行两个整数 Li,Ri。

## 输出格式

输出 Q 行，每行一个整数，表示答案。

## 样例

### 样例 1
输入：
```
5
5 2 1 5 3
3
1 4
2 5
1 5
```
输出：
```
12
9
12
```

## 提示

对于 100% 的数据，3≤N≤5×10^5，1≤Ai≤10^8，1≤Q≤5×10^5。

## 解题思路

### 问题分析
需要在区间内选择三个位置 a<b<c，满足 b-a≤c-b，使强度和最大。

### 核心思路
枚举中间点b，然后枚举a和c。

### 算法流程
1. 对每个询问，枚举中间点b
2. 枚举a和c，满足约束条件
3. 更新最大值

### 复杂度分析
- 时间复杂度：O(Q * N^2)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
int N, Q;
long long A[MAXN];
int L[MAXN], R[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &A[i]);
    }
    
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }
    
    for (int i = 1; i <= Q; i++) {
        long long ans = 0;
        
        for (int b = L[i] + 1; b < R[i]; b++) {
            for (int a = L[i]; a < b; a++) {
                int d1 = b - a;
                int max_c = min(R[i], b + d1);
                for (int c = b + 1; c <= max_c; c++) {
                    ans = max(ans, A[a] + A[b] + A[c]);
                }
            }
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}
```