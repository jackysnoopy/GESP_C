# [USACO10MAR] Barn Allocation G

## 题目描述

农夫约翰最近开了一个新的牲口棚。因为其中的一些畜栏风景更好，所以奶牛们向约翰发出了希望分配畜栏的申请。

牲口棚有 $N$ 个畜栏 $(1 \le N \le 100,000)$，方便起见，我们把它们编号为 $1 \sim N$，畜栏 $i$ 能容纳 $C_i$ 头牛 $(1 \le Ci \le 100,000)$。第 $i$ 头牛申请为它分配 $A_i$ 到 $B_i$ 的编号连续的畜栏来让它散步 $(1  \le A_i \le B_i \le N)$。换言之，这头奶牛希望能自由地访问畜栏 $A_i \sim B_i$，而为了满足它的要求，你需要在 $A_i \sim B_i$ 范围内的畜栏中为它预留至少一单位容量。

给出 $M$ 个畜栏分配请求 $(1 \le M \le 100,000)$，回答最多能满足多少头牛的要求而不增加额外的畜栏。

## 输入格式

第一行包括两个以空格隔开的正整数：$N,M$。

第二行到第 $N+1$ 行：第 $i+1$ 行每行包括一个整数：$C_i$。

第 $N+2$ 到第 $N+M+1$ 行：第 $i+N+1$ 行每行包括两个整数 $A_i,B_i$。

## 输出格式

仅一行：能满足的最大要求数。

## 样例

Sample 1:
Input:
5 4
1
3
2
1
3
1 3
2 5
2 3
4 5
Output:
3

## 提示

考虑以下例子：

畜栏号:      1   2   3   4   5
           +---+---+---+---+---+
容纳空间:   | 1 | 3 | 2 | 1 | 3 |  
           +---+---+---+---+---+
Cow 1       XXXXXXXXXXX             (1, 3)
Cow 2           XXXXXXXXXXXXXXX     (2, 5)
Cow 3           XXXXXXX             (2, 3)
Cow 4                   XXXXXXX     (4, 5)

Source: USACO 2010 March Gold

## 解题思路

### 问题分析
- 有 $N$ 个畜栏，每个畜栏有容量 $C_i$。
- 有 $M$ 头牛，每头牛申请区间 $[A_i, B_i]$ 内的畜栏。
- 每头牛需要在区间内分配至少一个单位容量。
- 目标是最大化满足的牛的数量。

### 核心思路
- 贪心策略：按右端点 $B_i$ 升序排序，优先处理结束位置早的请求。
- 对于每头牛，在区间 $[A_i, B_i]$ 内找到第一个容量大于 0 的位置进行分配。
- 使用线段树维护区间最小值，支持单点修改和区间查询。

### 算法流程
1. 将所有牛按右端点 $B_i$ 升序排序。
2. 构建线段树，维护每个畜栏的剩余容量。
3. 对于每头牛：
   - 查询区间 $[A_i, B_i]$ 的最小容量。
   - 如果最小容量大于 0，说明可以满足该请求。
   - 找到区间内第一个容量大于 0 的位置，将该位置的容量减 1。
4. 统计满足的牛的数量。

### 复杂度分析
- 时间复杂度：$O((N + M) \log N)$，排序 $O(M \log M)$，线段树操作 $O(\log N)$。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Cow {
    int a, b, idx;
};

int n, m;
int cap[100005];
int tree[400005];

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = cap[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(node * 2, l, mid, pos, val);
    else update(node * 2 + 1, mid + 1, r, pos, val);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 1e9;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return min(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
}

int findFirst(int node, int l, int r, int ql, int qr) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (qr <= mid) return findFirst(node * 2, l, mid, ql, qr);
    if (ql > mid) return findFirst(node * 2 + 1, mid + 1, r, ql, qr);
    if (tree[node * 2] > 0) return findFirst(node * 2 + 1, mid + 1, r, ql, qr);
    return findFirst(node * 2, l, mid, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> cap[i];
    }
    
    vector<Cow> cows(m);
    for (int i = 0; i < m; i++) {
        cin >> cows[i].a >> cows[i].b;
        cows[i].idx = i;
    }
    
    sort(cows.begin(), cows.end(), [](const Cow& x, const Cow& y) {
        return x.b < y.b || (x.b == y.b && x.a < y.a);
    });
    
    build(1, 1, n);
    
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int a = cows[i].a, b = cows[i].b;
        if (query(1, 1, n, a, b) > 0) {
            int pos = findFirst(1, 1, n, a, b);
            update(1, 1, n, pos, cap[pos] - 1);
            cap[pos]--;
            ans++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}

```
