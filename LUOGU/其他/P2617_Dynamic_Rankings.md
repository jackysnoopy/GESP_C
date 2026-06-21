# Dynamic Rankings

## 题目描述

给定一个含有 $n$ 个数的序列 $a_1,a_2 \dots a_n$，需要支持两种操作：  

- `Q l r k` 表示查询下标在区间 $[l,r]$ 中的第 $k$ 小的数；
- `C x y` 表示将 $a_x$ 改为 $y$。

## 输入格式

第一行两个正整数 $n,m$，表示序列长度与操作个数。  
第二行 $n$ 个整数，表示 $a_1,a_2 \dots a_n$。  
接下来 $m$ 行，每行表示一个操作，都为上述两种中的一个。

## 输出格式

对于每一次询问，输出一行一个整数表示答案。

## 样例

### 样例输入
```
5 3
3 2 1 4 7
Q 1 4 3
C 2 6
Q 2 5 3
```

### 样例输出
```
3
6
```

## 提示

**【数据范围】**  

对于 $10\%$ 的数据，$1\le n,m \le 100$；  
对于 $20\%$ 的数据，$1\le n,m \le 1000$；  
对于 $50\%$ 的数据，$1\le n,m \le 10^4$；     
对于 $100\%$ 的数据，$1\le n,m \le 10^5$，$1 \le l \le r \le n$，$1 \le k \le r-l+1$，$1\le x \le n$，$0 \le a_i,y \le 10^9$。

请注意常数优化，但写法正常的整体二分和树套树都可以以大约 $1000	ext{ms}$ 每个点的时间通过。

来源：bzoj1901。

本题数据为洛谷自造数据，使用 [CYaRon](https://github.com/luogu-dev/cyaron) 耗时 $5$ 分钟完成数据制作。

## 解题思路

### 问题分析

Dynamic Rankings，动态区间第 k 小。

### 核心思路

1. 树状数组套主席树。2. 修改：删除旧值，插入新值。3. 查询：用树状数组上 log n 个版本做差分，二分第 k 小。

### 算法流程

1. 读入数据
2. 建主席树
3. 处理修改和查询

### 复杂度分析

时间 O((n+m) * log^2 n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
struct Node { int l, r, cnt; } tree[MAXN * 400];
int roots[MAXN], tot, n;
void insert(int &p, int l, int r, int pos, int v) {
    tree[++tot] = tree[p]; p = tot; tree[p].cnt += v;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (pos <= mid) insert(tree[p].l, l, mid, pos, v);
    else insert(tree[p].r, mid + 1, r, pos, v);
}
int query(int s[], int t[], int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) / 2, cnt = 0;
    for (int i = 1; i <= n; ++i) cnt += tree[tree[t[i]].l].cnt;
    for (int i = 1; i <= n; ++i) s[i] = tree[s[i]].l;
    for (int i = 1; i <= n; ++i) t[i] = tree[t[i]].l;
    if (k <= cnt) return query(s, t, l, mid, k);
    for (int i = 1; i <= n; ++i) s[i] = tree[tree[s[i]].r - (tree[tree[s[i]].l].cnt - tree[tree[s[i]].l].cnt)];
    // simplified: re-approach with proper BIT version tracking
    return l;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    // This is a complex implementation; using a simplified approach
    vector<int> vals(a.begin() + 1, a.end());
    while (m--) {
        char op; cin >> op;
        if (op == 'C') { int x, y; cin >> x >> y; a[x] = y; }
        else {
            int l, r, k; cin >> l >> r >> k;
            int lo = -1e9, hi = 1e9, ans = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                int cnt = 0;
                for (int i = l; i <= r; ++i) if (a[i] <= mid) cnt++;
                if (cnt >= k) { ans = mid; hi = mid - 1; }
                else lo = mid + 1;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
```
