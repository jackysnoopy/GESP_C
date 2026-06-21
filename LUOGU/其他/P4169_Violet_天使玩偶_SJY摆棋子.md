# [Violet] 天使玩偶/SJY摆棋子

## 题目描述

Ayu 在七年前曾经收到过一个天使玩偶，当时她把它当作时间囊埋在了地下。而七年后 的今天，Ayu 却忘了她把天使玩偶埋在了哪里，所以她决定仅凭一点模糊的记忆来寻找它。

我们把 Ayu 生活的小镇看作一个二维平面坐标系，而 Ayu 会不定时地记起可能在某个点 $(x, y)$ 埋下了天使玩偶；或者 Ayu 会询问你，假如她在 $(x,y)$，那么她离近的天使玩偶可能埋下的地方有多远。

因为 Ayu 只会沿着平行坐标轴的方向来行动，所以在这个问题里我们定义两个点之间的距离为 $\operatorname{dist}(A,B)=|A_x-B_x|+|A_y-B_y|$。其中 $A_x$ 表示点 $A$ 的横坐标，其余类似。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，在刚开始时，Ayu 已经知道有 $n$ 个点可能埋着天使玩偶， 接下来 Ayu 要进行 $m$ 次操作。

接下来 $n$ 行，每行两个非负整数 $(x_i,y_i)$，表示初始 $n$ 个点的坐标。

再接下来 $m$ 行，每行三个非负整数 $t,x_i,y_i$。

* 如果 $t=1$，则表示 Ayu 又回忆起了一个可能埋着玩偶的点 $(x_i,y_i)$。
* 如果 $t=2$，则表示 Ayu 询问如果她在点 $(x_i,y_i)$，那么在已经回忆出来的点里，离她近的那个点有多远

## 输出格式

对于每个 $t=2$ 的询问，在单独的一行内输出该询问的结果。

## 样例

### 样例输入
```
2 3 
1 1 
2 3 
2 1 2 
1 3 3 
2 4 2
```

### 样例输出
```
1 
2
```

## 提示

#### 数据规模与约定

对于 $100\%$ 的数据 保证 $1 \leq n,m\leq 3 	imes 10^5$，$0 \leq x_i,y_i \leq 10^6$。

## 解题思路

### 问题分析

天使玩偶，动态加点 + 曼哈顿距离最近点查询。

### 核心思路

1. CDQ 分治，每层扫描处理跨左右的贡献。2. 曼哈顿距离分四个象限，每个象限用树状数组求最近距离。3. 操作分为插入点和查询最近距离。

### 算法流程

1. 读入操作
2. CDQ 分治 + 树状数组
3. 输出查询结果

### 复杂度分析

时间 O(n * log^2 n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 500001;
const int INF = 1e9;
int tree[MAXN * 4];
void update(int p, int l, int r, int pos, int v) {
    if (l == r) { tree[p] = min(tree[p], v); return; }
    int mid = (l + r) / 2;
    if (pos <= mid) update(p*2, l, mid, pos, v);
    else update(p*2+1, mid+1, r, pos, v);
    tree[p] = min(tree[p*2], tree[p*2+1]);
}
int query(int p, int l, int r, int L, int R) {
    if (L > R) return INF;
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2, res = INF;
    if (L <= mid) res = min(res, query(p*2, l, mid, L, R));
    if (R > mid) res = min(res, query(p*2+1, mid+1, r, L, R));
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> tx(n + m + 1), ty(n + m + 1), top(n + m + 1), ans(m + 1, INF);
    for (int i = 1; i <= n; ++i) { cin >> tx[i] >> ty[i]; top[i] = 0; }
    int cnt = n;
    for (int i = 1; i <= m; ++i) {
        int op; cin >> op;
        if (op == 1) { cnt++; cin >> tx[cnt] >> ty[cnt]; top[cnt] = 1; }
        else { cnt++; cin >> tx[cnt] >> ty[cnt]; top[cnt] = 2; }
    }
    int mx = *max_element(tx.begin() + 1, tx.begin() + cnt + 1);
    for (int dir = 0; dir < 4; ++dir) {
        for (int i = 0; i <= mx * 4 + 10; ++i) tree[i] = INF;
        vector<int> ord(cnt);
        for (int i = 1; i <= cnt; ++i) ord[i - 1] = i;
        if (dir == 0) sort(ord.begin(), ord.end(), [](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); });
        else if (dir == 1) { for (int i = 1; i <= cnt; ++i) ty[i] = -ty[i]; sort(ord.begin(), ord.end(), [](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); }); }
        else if (dir == 2) { for (int i = 1; i <= cnt; ++i) tx[i] = -tx[i]; sort(ord.begin(), ord.end(), [](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); }); }
        else { for (int i = 1; i <= cnt; ++i) { tx[i] = -tx[i]; ty[i] = -ty[i]; } sort(ord.begin(), ord.end(), [](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); }); }
        for (int i : ord) {
            if (top[i] == 0) { update(1, 0, mx, ty[i], tx[i] + ty[i]); }
            else if (top[i] == 2) {
                int d = query(1, 0, mx, 0, ty[i]);
                if (d < INF) ans[i - n] = min(ans[i - n], tx[i] + ty[i] - d);
            }
        }
        for (int i = 1; i <= cnt; ++i) { if (dir & 1) ty[i] = -ty[i]; else tx[i] = -tx[i]; }
    }
    for (int i = 1; i <= m; ++i) if (ans[i] < INF) cout << ans[i] << '\n';
    return 0;
}
```
