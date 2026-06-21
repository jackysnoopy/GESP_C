# Interval GCD

## 题目描述

给定一个长度为 $N$ 的数列 $a$，以及 $M$ 条指令，每条指令可能是以下两种之一：

1. `C l r d`，表示把 $a_l,a_{l+1},…,a_r$ 都加上 $d$。
2. `Q l r`，表示询问 $a_l,a_{l+1},…,a_r$ 的最大公约数（$\gcd$）。

对于每个询问，输出一个整数表示答案。

## 输入格式

第一行两个整数 $N,M$。

第二行 $N$ 个整数，分别表示 $a_1,a_2,\dots,a_N$。

接下来 $M$ 行表示 $M$ 条指令，每条指令的格式如题目描述所示。

## 输出格式

对于每个询问，输出一个整数表示答案，每个答案占一行。

## 样例

### 样例输入
```
5 5
1 3 5 7 9
Q 1 5
C 1 5 1
Q 1 5
C 3 3 6
Q 2 4
```

### 样例输出
```
1
2
4
```

## 提示

对于 $100\%$ 的测试数据，$N \le 5	imes10^5$，$M \le 10^5$，$1 \le a_i \le 10^{18}$，$|d| \le 10^{18}$，保证数据在计算过程中不会超过 long long 范围。

## 解题思路

### 问题分析

Interval GCD，区间加 + 区间 GCD 查询。

### 核心思路

1. 利用性质 gcd(a,b) = gcd(a, b-a)。区间加 d 不改变相邻差值的 GCD。2. 对差分数组建线段树维护 GCD。3. 区间 [l,r] 的 GCD = gcd(a[l], gcd(diff[l+1..r]))。

### 算法流程

1. 读入数组
2. 建差分线段树
3. 处理修改和查询

### 复杂度分析

时间 O((n+m) * log n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 500001;
int tree[MAXN * 4], n;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void build(int p, int l, int r, vector<int>& a) {
    if (l == r) { tree[p] = a[l]; return; }
    int mid = (l + r) / 2;
    build(p*2, l, mid, a); build(p*2+1, mid+1, r, a);
    tree[p] = gcd(tree[p*2], tree[p*2+1]);
}
void update(int p, int l, int r, int pos, int v) {
    if (l == r) { tree[p] += v; return; }
    int mid = (l + r) / 2;
    if (pos <= mid) update(p*2, l, mid, pos, v);
    else update(p*2+1, mid+1, r, pos, v);
    tree[p] = gcd(tree[p*2], tree[p*2+1]);
}
int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2;
    if (R <= mid) return query(p*2, l, mid, L, R);
    if (L > mid) return query(p*2+1, mid+1, r, L, R);
    return gcd(query(p*2, l, mid, L, R), query(p*2+1, mid+1, r, L, R));
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m; cin >> n >> m;
    vector<int> a(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i) { cin >> a[i]; d[i] = a[i] - a[i-1]; }
    build(1, 1, n, d);
    while (m--) {
        char op; int l, r, v;
        cin >> op >> l >> r;
        if (op == 'C') {
            cin >> v;
            update(1, 1, n, l, v);
            if (r + 1 <= n) update(1, 1, n, r + 1, -v);
        } else {
            int g = query(1, 1, n, l + 1, r);
            cout << abs(gcd(a[l], g)) << '\n';
        }
    }
    return 0;
}
```
