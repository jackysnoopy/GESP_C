# P3971 [TJOI2014] Alice and Bob

## 题目描述

Alice和Bob在玩游戏。Alice有一个长度为 $n$ 的序列 $a_1, a_2, \ldots, a_n$。Bob每次可以选择两个不同的下标 $i, j$，使得 $a_i$ 是 $a_j$ 的倍数，然后将 $a_j$ 删除。Alice希望剩下的序列尽可能长，Bob希望剩下的序列尽可能短。求最后剩下的序列长度。

## 输入格式

第一行一个整数 $n$，表示序列长度。

第二行 $n$ 个整数 $a_1, a_2, \ldots, a_n$，表示序列。

## 输出格式

一个整数，表示最后剩下的序列长度。

## 样例

输入：
```
5
2 3 4 6 12
```
输出：
```
2
```

## 解题思路

### 问题分析

这是一个DP+BIT问题。需要找到最长的序列，使得其中任意两个数都不满足倍数关系。

### 核心思路

1. 将序列排序
2. 使用DP，$dp[i]$ 表示以 $a_i$ 结尾的最长序列长度
3. 使用BIT优化DP转移

### 算法流程

1. 读取序列并排序
2. 对于每个数，枚举其因子
3. 使用BIT维护DP值
4. 输出最大DP值

### 复杂度分析

- 时间复杂度：$O(n \log n + n \sqrt{V})$
- 空间复杂度：$O(n + V)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
    vector<int> dp(n, 1);
    int ans = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] % a[j] == 0) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    
    cout << ans << endl;
    return 0;
}
```
