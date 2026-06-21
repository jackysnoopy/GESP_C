# [CEOI 1999] Parity Game

## 题目描述

Alice 和 Bob 在玩一个游戏：他写一个由 $0$ 和 $1$ 组成的序列。Alice 选其中的一段（比如第 $3$ 位到第 $5$ 位），问他这段里面有奇数个 $1$ 还是偶数个 $1$。Bob 回答你的问题，然后 Alice 继续问。Alice 要检查 Bob 的答案，指出在 Bob 的第几个回答一定有问题。有问题的意思就是存在一个 $01$ 序列满足这个回答前的所有回答，而且不存在序列满足这个回答前的所有回答及这个回答。

## 输入格式

第 $1$ 行一个整数 $n$，是这个 $01$ 序列的长度。

第 $2$ 行一个整数 $m$，是问题和答案的个数。

第 $3$ 行开始是问题和答案，每行先有两个整数，表示你询问的段的开始位置和结束位置。然后是 Bob 的回答。`odd`表示有奇数个 $1$，`even` 表示有偶数个 $1$。

## 输出格式

输出一行，一个数 $x$，表示存在一个 $01$ 序列满足第 $1$ 到第 $x$ 个回答，但是不存在序列满足第 $1$ 到第 $x+1$ 个回答。如果所有回答都没问题，你就输出所有回答的个数。

## 样例

### 样例输入
```
10
5
1 2 even
3 4 odd
5 6 even
1 6 even
7 10 odd
```

### 样例输出
```
3
```

## 提示

对于 $100\%$ 的数据，$1 \le  n \leq 10^9$，$m \leq 5 	imes 10^3$。

## 解题思路

### 问题分析

Parity Game，判断 Bob 哪次开始说谎。

### 核心思路

1. 用前缀和奇偶性建立关系：s[i]-s[j] 的奇偶性。2. 带权并查集维护到根的距离（mod 2）。3. 离散化后依次合并，出现矛盾即为答案。

### 算法流程

1. 读入约束
2. 离散化
3. 带权并查集依次检查
4. 输出首次矛盾位置

### 复杂度分析

时间 O(n * α(n))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int fa[500001], rk[500001], dist[500001];
int find(int x) {
    if (fa[x] == x) return x;
    int r = find(fa[x]);
    dist[x] ^= dist[fa[x]];
    fa[x] = r; return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> vals = {0};
    vector<tuple<int,int,int>> cons;
    for (int i = 0; i < n; ++i) {
        int a,b; string s;
        cin >> a >> b >> s;
        int t = (s == "odd") ? 1 : 0;
        vals.push_back(a-1); vals.push_back(b);
        cons.push_back({a-1, b, t});
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto getId = [&](int x) { return lower_bound(vals.begin(), vals.end(), x) - vals.begin(); };
    int m = vals.size();
    for (int i = 0; i < m; ++i) { fa[i] = i; rk[i] = 0; dist[i] = 0; }
    int ans = n;
    for (int i = 0; i < n; ++i) {
        int a,b,t; tie(a,b,t) = cons[i];
        a = getId(a); b = getId(b);
        int ra = find(a), rb = find(b);
        if (ra == rb) {
            if ((dist[a] ^ dist[b]) != t) { ans = i; break; }
        } else {
            if (rk[ra] < rk[rb]) { fa[ra] = rb; dist[ra] = dist[a] ^ dist[b] ^ t; }
            else { fa[rb] = ra; dist[rb] = dist[a] ^ dist[b] ^ t; if (rk[ra] == rk[rb]) rk[ra]++; }
        }
    }
    cout << ans << '\n';
    return 0;
}
```
