# [USACO16FEB] Circular Barn G

## 题目描述

有 $n$ 个房间排成环形，第 $i$ 个房间有 $c_i$ 头奶牛（$\sum c_i = n$）。奶牛顺时针穿过 $d$ 扇门消耗 $d^2$ 能量。求将所有奶牛重新分配，使得每个房间恰好有 1 头奶牛的最小总能量。

## 输入格式

第一行一个整数 $n$。  
接下来 $n$ 行，每行一个整数 $c_i$。

## 输出格式

一个整数，最小总能量。

## 样例

**输入：**
```
10
1
0
0
2
0
0
1
2
2
2
```

**输出：**
```
33
```

## 提示

$1 \le n \le 1000$，$0 \le c_i \le n$，$\sum c_i = n$。

## 解题思路

### 问题分析

- $n$ 个房间排成环形，总共有 $n$ 头奶牛
- 目标：重新分配使得每个房间恰好 1 头奶牛
- 奶牛移动 $d$ 扇门消耗 $d^2$ 能量
- 求最小总能量

### 核心思路

由于是环形结构，关键在于**断环为链**。对于每种断环方式（即选择不同的起始点），可以将环展开为链，然后贪心分配奶牛：

1. 枚举断环的起点（共 $n$ 种）
2. 对于每种断法，将环展开为链
3. 在链上贪心分配：每头奶牛移动到离它最近的空房间
4. 由于费用是 $d^2$（凸函数），每段奶牛的最优汇聚点在**加权中位数**处

### 算法流程

1. 枚举每个房间作为起点，将环展开为链
2. 对于每种展开方式，依次将奶牛分配到目标房间
3. 计算每头奶牛移动的距离平方和
4. 取所有断法中的最小值

### 复杂度分析

- 时间复杂度：$O(n^2)$（枚举 $n$ 个起点，每个起点计算 $O(n)$）
- 空间复杂度：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    long long ans = LLONG_MAX;

    for (int start = 0; start < n; start++) {
        long long cost = 0;
        int pos = 0;
        for (int i = 0; i < n; i++) {
            int idx = (start + i) % n;
            for (int j = 0; j < c[idx]; j++) {
                int d = (pos - i + n) % n;
                cost += (long long)d * d;
                pos++;
            }
        }
        ans = min(ans, cost);
    }

    cout << ans << "\n";
    return 0;
}
```
