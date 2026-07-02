# [GCJ 2014 #1C] Enclosure

## 题目描述

在 N×M 网格上放石头，使得至少 K 个交叉点被围住。求最少石头数。

## 输入格式

第一行 T。
每个用例一行 N M K。

## 输出格式

输出 Case #x: y。

## 样例

### 样例 1
输入：
```
2
4 5 8
3 5 11
```
输出：
```
Case #1: 6
Case #2: 8
```

## 提示

- 1 ≤ N×M ≤ 1000

## 解题思路

### 问题分析

需要最少石头围住至少 K 个点。

### 核心思路

1. 围成矩形最优
2. 枚举矩形大小
3. 计算边界石头数

### 算法流程

1. 枚举可能的矩形大小
2. 计算所需石头数
3. 取最小值

### 复杂度分析

- 时间复杂度：O(N×M)
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M, K;
        cin >> N >> M >> K;
        
        int ans = 0;
        for (int h = 1; h <= N - 1; h++) {
            for (int w = 1; w <= M - 1; w++) {
                if (h * w >= K) {
                    int stones = 2 * (h + w);
                    if (ans == 0 || stones < ans) ans = stones;
                }
            }
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    return 0;
}
```
