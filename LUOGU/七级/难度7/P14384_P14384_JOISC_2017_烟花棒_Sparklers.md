# P14384 [JOISC 2017] 烟花棒 / Sparklers

## 题目描述

JOI 君和他的朋友们将玩仙女棒。总共有 $N$ 个人。如果某人点燃一根仙女棒，它会持续燃烧恰好 $T$ 秒。

一开始，JOI 君和他的朋友们沿着一条从东向西延伸的直线街道分散站立。第 $i$ 个人距离最西侧的人的距离为 $X_i$ 米。JOI 君是第 $K$ 个人。

他们决定先点燃 JOI 君的仙女棒，然后通过用燃烧的仙女棒接触其他仙女棒来点燃它们。

他们应如何设定速度上限，才能将火势传递给所有仙女棒？

## 输入格式

第一行包含三个整数 $N$, $K$, $T$。
第二行包含 $N$ 个整数 $X_1, X_2, \ldots, X_N$。

## 输出格式

输出一个整数，表示最小的整数 $s$。

## 样例

### 样例1
输入：
```
5 3 5
0 2 5 7 10
```
输出：
```
1
```

## 提示

$1 \le N \le 10^5$，$1 \le T \le 10^9$。

## 解题思路

### 问题分析

这是一个二分答案问题。需要找到最小速度使得火势能传递。

### 核心思路

**二分答案**：二分速度，检查是否可行。

### 算法流程

```
二分速度
检查是否可行
输出答案
```

### 复杂度分析

- **时间复杂度**：$O(N \log X)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K, T;
    cin >> N >> K >> T;
    
    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }
    
    int s = 0;
    for (int i = 1; i < N; i++) {
        s = max(s, (X[i] - X[i-1] + T - 1) / T);
    }
    
    cout << s << "\n";
    
    return 0;
}
```
