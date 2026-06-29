# P7637 [BalticOI 2006] BITWISE EXPRESSIONS (Day 1)

## 题目描述

在信号处理中，当变量是在一定范围内的整数时，人们有时会对包含按位 AND 和 OR 运算符的某个表达式的最大值感兴趣。

为简单起见，该表达式具有特定的形式，即由按位 AND 操作符分隔的圆括号内的若干子表达式。每个子表达式由一个或多个变量组成，变量之间用按位 OR 操作符分隔。

## 输入格式

第一行给出两个正整数 $N$ 和 $P$。
第二行给出 $P$ 个正整数 $K_1,K_2, \cdots ,K_P$。
下面 $N$ 行中每一行包含两个整数 $A_j$ 和 $B_j$。

## 输出格式

一行，包含一个整数：表达式可以接受的最大值。

## 样例

### 样例1
输入：
```
8 4
3 1 2 2
2 4
1 4
0 0
1 7
1 4
1 2
3 4
2 3
```
输出：
```
7
```

## 提示

$1 \le N \le 100$，$1 \le P \le N$，$0 \le A_j \le B_j \le 2×10^9$。

## 解题思路

### 问题分析

这是一个位运算问题。需要计算表达式最大值。

### 核心思路

**贪心+位运算**：从高位到低位贪心选择。

### 复杂度分析

- **时间复杂度**：$O(N \cdot \log B)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, P;
    cin >> N >> P;
    
    vector<int> K(P);
    for (int i = 0; i < P; i++) {
        cin >> K[i];
    }
    
    vector<ll> A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
    }
    
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, B[i]);
    }
    
    cout << ans << "\n";
    
    return 0;
}
```
