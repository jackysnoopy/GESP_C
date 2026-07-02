# [CCC 2025 Senior] 写作业 / To-Do List

## 题目描述

你的待办事项列表现在是空的。你需要处理 $q$ 次对待办事项列表的更新：

- **A $s$ $t$**：加入一个任务，在第 $s$ 秒发布，需要 $t$ 秒完成。
- **D $x$**：删除第 $x$ 个被加入的任务。

每次操作后，求出最早能在什么时候完成列表中所有任务。一次只能完成一个任务，一旦开始必须一口气完成。

操作是加密的：令 $p=10^6+3$，$\mathrm{last}$ 为上一次答案。$s=(s'+\mathrm{last})\bmod p$，$t=(t'+\mathrm{last})\bmod p$，$x=(x'+\mathrm{last})\bmod p$。

## 输入格式

第一行，一个正整数 $q$。

接下来 $q$ 行，每行一个大写字母 $c\in \texttt{A},\texttt{D}$ 和若干个非负整数，描述一次加密的操作。

## 输出格式

输出 $q$ 行，每行一个正整数，表示答案。

## 样例

### 样例 1

**输入：**
```
6
A 3 3
A 2 0
A 999996 999995
D 999991
A 1000000 999994
D 999992
```

**输出：**
```
5
11
13
11
13
9
```

### 样例 2

**输入：**
```
2
A 1000000 1000000
A 4 4
```

**输出：**
```
1999999
2999999
```

## 解题思路

### 问题分析

将任务按发布时间 $s$ 排序后，最优策略是按 $s$ 从小到大依次执行。对于排序后的任务序列 $s_1 \le s_2 \le \cdots \le s_n$，每个任务的完成时间为：

$$\text{finish}_i = \max(s_i, \text{finish}_{i-1}) + t_i$$

最终答案为 $\text{finish}_n$。

### 核心思路

设 $f(s_i) = s_i + \sum_{j: s_j \ge s_i} t_j$，即任务 $i$ 的发布时刻加上所有发布时间 $\ge s_i$ 的任务的总时长。可以证明答案就是 $\max_i f(s_i)$。

**关键观察**：
- 插入新任务 $(s_{\text{new}}, t_{\text{new}})$ 时：所有 $s < s_{\text{new}}$ 的任务的 $f$ 值增加 $t_{\text{new}}$，$s \ge s_{\text{new}}$ 的任务不变，新任务本身 $f = s_{\text{new}} + t_{\text{new}}$。
- 删除任务 $(s_{\text{del}}, t_{\text{del}})$ 时：所有 $s < s_{\text{del}}$ 的任务的 $f$ 值减少 $t_{\text{del}}$，$s > s_{\text{del}}$ 的任务不变。

因此，可以用**线段树**（支持区间加、区间最大值查询）维护所有位置的 $f$ 值：
- 插入时：区间 $[1, s-1]$ 加 $t$，将位置 $s$ 设为 $s+t$。
- 删除时：区间 $[1, s-1]$ 减 $t$，将位置 $s$ 设为 $0$。
- 答案即线段树全局最大值。

### 算法流程

1. 建立线段树，支持区间加和区间最大值查询。
2. 维护 `taskVal[s]` 记录当前发布时刻为 $s$ 的任务的 $f$ 值。
3. 对于每个操作：
   - **A**：解密 $s, t$，执行区间加和单点赋值。
   - **D**：解密 $x$，取出任务的 $s$ 和 $t$，执行区间减和单点清零。
4. 输出全局最大值作为答案。

### 复杂度分析

- 时间复杂度：$O(q \log V)$，其中 $V = 10^6$ 为最大发布时间。
- 空间复杂度：$O(V)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000002;
const long long INF = 1e18;

long long tree[MAXN * 4];
long long lazy[MAXN * 4];

void push(int node) {
    if (lazy[node] != 0) {
        tree[node * 2] += lazy[node];
        lazy[node * 2] += lazy[node];
        tree[node * 2 + 1] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void pull(int node) {
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

void update(int node, int l, int r, int ql, int qr, long long val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    push(node);
    int mid = (l + r) / 2;
    update(node * 2, l, mid, ql, qr, val);
    update(node * 2 + 1, mid + 1, r, ql, qr, val);
    pull(node);
}

void setPoint(int node, int l, int r, int pos, long long val) {
    if (l == r) {
        tree[node] = val;
        lazy[node] = 0;
        return;
    }
    push(node);
    int mid = (l + r) / 2;
    if (pos <= mid)
        setPoint(node * 2, l, mid, pos, val);
    else
        setPoint(node * 2 + 1, mid + 1, r, pos, val);
    pull(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    const int MOD = 1000003;
    long long last = 0;

    vector<long long> taskVal(MAXN, 0);

    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == 'A') {
            long long sp, tp;
            cin >> sp >> tp;
            long long s = (sp + last) % MOD;
            long long t = (tp + last) % MOD;
            if (s == 0) s = MOD;
            if (t == 0) t = MOD;

            if (s > 1)
                update(1, 1, MAXN - 1, 1, s - 1, t);
            setPoint(1, 1, MAXN - 1, s, s + t);
            taskVal[s] = s + t;
        } else {
            long long xp;
            cin >> xp;
            long long x = (xp + last) % MOD;
            if (x == 0) x = MOD;

            long long s = x;
            long long t = taskVal[x] - s;

            if (s > 1)
                update(1, 1, MAXN - 1, 1, s - 1, -t);
            setPoint(1, 1, MAXN - 1, s, 0);
            taskVal[s] = 0;
        }

        last = tree[1];
        cout << last << "\n";
    }

    return 0;
}
```
