# GSS3 - Can you answer these queries III

## 题目描述

You are given a sequence A of N (N <= 50000) integers between -10000 and 10000. On this sequence you have to apply M (M <= 50000) operations:   
 modify the i-th element in the sequence or for given x y print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输入格式

The first line of input contains an integer N. The following line contains N integers, representing the sequence A1..AN.   
 The third line contains an integer M. The next M lines contain the operations in following form:  
 0 x y: modify Ax into y (|y|<=10000).  
 1 x y: print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输出格式

For each query, print an integer as the problem required.

## 样例

### 样例输入
```
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3
```

### 样例输出
```
6
4
-3
```

## 提示



## 解题思路

### 问题分析

GSS3，区间最大子段和 + 单点修改。

### 核心思路

1. 线段树节点维护：区间最大子段和、最大前缀和、最大后缀和、区间和。2. 合并两个子区间时计算新的最大子段和。

### 算法流程

1. 建线段树
2. 处理修改和查询

### 复杂度分析

时间 O((n+m) * log n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 50001;
const int INF = -1e9;
struct Node { int sum, pre, suf, mx; } tree[MAXN * 4];
int n;
Node merge(Node a, Node b) {
    Node c;
    c.sum = a.sum + b.sum;
    c.pre = max(a.pre, a.sum + b.pre);
    c.suf = max(b.suf, b.sum + a.suf);
    c.mx = max(max(a.mx, b.mx), a.suf + b.pre);
    return c;
}
void build(int p, int l, int r, vector<int>& a) {
    if (l == r) { tree[p] = {a[l], a[l], a[l], a[l]}; return; }
    int mid = (l + r) / 2;
    build(p*2, l, mid, a); build(p*2+1, mid+1, r, a);
    tree[p] = merge(tree[p*2], tree[p*2+1]);
}
void update(int p, int l, int r, int pos, int v) {
    if (l == r) { tree[p] = {v, v, v, v}; return; }
    int mid = (l + r) / 2;
    if (pos <= mid) update(p*2, l, mid, pos, v);
    else update(p*2+1, mid+1, r, pos, v);
    tree[p] = merge(tree[p*2], tree[p*2+1]);
}
Node query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2;
    if (R <= mid) return query(p*2, l, mid, L, R);
    if (L > mid) return query(p*2+1, mid+1, r, L, R);
    return merge(query(p*2, l, mid, L, R), query(p*2+1, mid+1, r, L, R));
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n, a);
    int m; cin >> m;
    while (m--) {
        int op, x, y; cin >> op >> x >> y;
        if (op == 0) update(1, 1, n, x, y);
        else cout << query(1, 1, n, x, y).mx << '\n';
    }
    return 0;
}
```
