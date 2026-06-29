# P11608 [PA 2016] 雨后的蘑菇 2 / Grzyby po deszczu 2

## 题目描述

给定长度为 $n$ 的整数数列 $a_1,\ldots,a_n$ 和 $b_1,\ldots,b_n$。

第 $1$ 天早上，第 $i$ 块地上有 $b_i$ 个蘑菇。每天的晚上，第 $i$ 块地上都会长出 $a_i$ 个蘑菇。

采蘑菇只能在早上进行，一次只能在一块地上采集，一次采集的数量没有限制。

对于 $k=1,2,\cdots,n$，求出：如果在前 $k$ 天**每天早上**选择一块地采蘑菇，最多能采多少个蘑菇？

## 输入格式

第一行，一个正整数 $n$。
接下来 $n$ 行，每行两个非负整数 $a_i,b_i$。

## 输出格式

输出 $n$ 行，第 $i$ 行一个整数，表示 $k=i$ 时的答案。

## 样例

### 样例1
输入：
```
3
5 10
16 0
5 10
```
输出：
```
10
26
57
```

## 提示

- $1\le n\le 10^6$；
- $0\le a_i\le 10^6$；
- $0\le b_i\le 10^{12}$。

## 解题思路

### 问题分析

这是一个贪心问题。每天需要选择一块地采蘑菇，使得总收获最大。

### 核心思路

**贪心策略**：每天选择当前蘑菇最多的地采蘑菇。

### 算法流程

```
for k = 1 to n:
    初始化蘑菇数量
    for day = 1 to k:
        选择蘑菇最多的地采蘑菇
        晚上长出新蘑菇
    输出总收获
```

### 复杂度分析

- **时间复杂度**：$O(n^2)$（暴力）
- **空间复杂度**：$O(n)$

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
    
    int n;
    cin >> n;
    
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    
    for (int k = 1; k <= n; k++) {
        ll total = 0;
        
        vector<ll> mushrooms(n);
        for (int i = 0; i < n; i++) {
            mushrooms[i] = b[i];
        }
        
        for (int day = 0; day < k; day++) {
            int best = 0;
            for (int i = 1; i < n; i++) {
                if (mushrooms[i] > mushrooms[best]) {
                    best = i;
                }
            }
            
            total += mushrooms[best];
            mushrooms[best] += a[best];
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
```
