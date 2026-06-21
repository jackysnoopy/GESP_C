# [USACO03OPEN] Lost Cows

## 题目描述

有 $N (2 \leq N \leq 8000)$ 头奶牛，它们在编号范围 $[1,N]$ 内具有唯一的标号。在一个极其糟糕的判断展示中，它们去了附近的“水坑”，在晚饭前喝了太多啤酒。到了排队吃晚饭的时候，它们没有按照编号升序的顺序排队。可惜的是，FJ 没有办法对它们进行排序。

此外，他在观察问题方面也不太擅长。他没有记下每头奶牛的编号，而是得到了一个相当愚蠢的统计数据：对于队伍中的每一头奶牛，他知道在这头奶牛之前，有多少头奶牛的编号确实比它小。给定这些数据，请告诉 FJ 奶牛的精确排列顺序。

## 输入格式

第 1 行，一个整数 $N$。

第 2 到第 $N$ 行，这 $N-1$ 行描述了在队伍中某头奶牛之前有多少头奶牛的编号比她小。

当然，没有奶牛排在第 1 头奶牛前面，所以她没有被列出。第 2 行描述了排在第 2 个位置的奶牛之前，有多少奶牛的编号比她小；第 3 行描述了排在第 3 个位置的奶牛之前，有多少奶牛的编号比她小；依此类推。

## 输出格式

第 1 到第 $N$ 行，输出的这 $N$ 行中的每一行表示排队中的一头奶牛的编号。输出的第 1 行表示排在队伍第 1 个位置的奶牛的编号；第 2 行表示排在第 2 个位置的奶牛的编号；依此类推。

## 样例

### 样例输入
```
5
1
2
1
0
```

### 样例输出
```
2
4
5
3
1
```

## 提示



## 解题思路

### 问题分析

Lost Cows，已知每头牛前面有多少头比它编号小的牛，求原始排列。

### 核心思路

1. 从最后一头牛往前推。第 i 头牛前面有 v[i] 头比它小，说明它是剩余未确定编号中第 (v[i]+1) 小的。2. 用树状数组维护可用编号集合，二分查找第 k 小。

### 算法流程

1. 读入 v 数组
2. 从后往前推
3. 树状数组二分查找第 k 小
4. 输出排列

### 复杂度分析

时间 O(n * log^2 n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 8001;
int tr[MAXN], n;
void add(int i, int v) { for (; i <= n; i += i & (-i)) tr[i] += v; }
int sum(int i) { int s = 0; for (; i > 0; i -= i & (-i)) s += tr[i]; return s; }
int kth(int k) {
    int pos = 0;
    for (int pw = 1 << 12; pw > 0; pw >>= 1)
        if (pos + pw <= n && tr[pos + pw] < k) { pos += pw; k -= tr[pos]; }
    return pos + 1;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    vector<int> v(n + 1), ans(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 1; i <= n; ++i) add(i, 1);
    for (int i = n; i >= 1; --i) {
        int k = v[i] + 1;
        int val = kth(k);
        ans[i] = val;
        add(val, -1);
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
    return 0;
}
```
