# Georgia and Bob

## 题目描述

有一个无限长的棋盘，从左到右编号为 $1,2,3,\cdots$。有 $n$ 个棋子在棋盘上，定义一次操作为把一枚棋子向左移动至少一格，不可以逾越其他棋子，不可与其他棋子重合，不可移出棋盘。

告诉你这 $n$ 个棋子的位置（不保证顺序且保证没有棋子重合），Georgia 和 Bob 轮流进行操作，Georgia 先手，谁无法操作谁输。问最后谁会赢？

![](https://cdn.luogu.com.cn/upload/image_hosting/tti7635d.png)

## 输入格式

**本题有多组数据**。

第一行一个整数 $T$（$1\leq T\leq 20$），表示数据组数。

对于每组数据：

第一行一个整数 $n$（$1\leq n\leq 1000$）。  

接下来一行 $n$ 个整数，表示每个棋子的位置 $P_i$（$1\leq P_i\leq 10000$）。

## 输出格式

对于每组数据，若 Georgia 胜输出 `Georgia will win`，若 Bob 胜输出 `Bob will win`，若平局则输出 `Not sure`。

## 样例

### 样例输入
```
2
3
1 2 3
8
1 5 6 7 9 12 14 17
```

### 样例输出
```
Bob will win
Georgia will win
```

## 提示



## 解题思路

### 问题分析

Georgia and Bob，棋子向左移动，阶梯 Nim 博弈。

### 核心思路

1. 将棋子按位置排序，相邻棋子间距为堆大小。
2. 阶梯 Nim：只看奇数位置的间距，XOR 决胜负。
3. 若 XOR != 0 先手胜（Georgia will win），否则 Bob 胜。

### 算法流程

1. 读入棋子位置
2. 排序，计算奇数间距
3. XOR 求值
4. 输出胜负

### 复杂度分析

时间 O(n log n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());
        int xr = 0;
        for (int i = n - 1; i >= 1; i -= 2)
            xr ^= a[i] - a[i - 1] - 1;
        cout << (xr ? "Georgia will win" : "Bob will win") << '\n';
    }
    return 0;
}
```
