# [Violet] 蒲公英

## 题目描述

在乡下的小路旁种着许多蒲公英，而我们的问题正是与这些蒲公英有关。

为了简化起见，我们把所有的蒲公英看成一个长度为 $n$ 的序列 $\{a_1,a_2..a_n\}$，其中 $a_i$ 为一个正整数，表示第 $i$ 棵蒲公英的种类编号。

而每次询问一个区间 $[l, r]$，你需要回答区间里出现次数最多的是哪种蒲公英，如果有若干种蒲公英出现次数相同，则输出种类编号最小的那个。

**注意，你的算法必须是在线的**。

## 输入格式

第一行有两个整数，分别表示蒲公英的数量 $n$ 和询问次数 $m$。

第二行有 $n$ 个整数，第 $i$ 个整数表示第 $i$ 棵蒲公英的种类 $a_i$。

接下来 $m$ 行，每行两个整数 $l_0, r_0$，表示一次询问。输入是加密的，解密方法如下：

令上次询问的结果为 $x$（如果这是第一次询问，则 $x = 0$），设 $l=((l_0+x-1)\bmod n) + 1,r=((r_0+x-1) \bmod n) + 1$。如果 $l > r$，则交换 $l, r$。  
最终的询问区间为计算后的 $[l, r]$。

## 输出格式

对于每次询问，输出一行一个整数表示答案。

## 样例

### 样例输入
```
6 3 
1 2 3 2 1 2 
1 5 
3 6 
1 5
```

### 样例输出
```
1 
2 
1
```

## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n,m \le 3000$。
- 对于 $100\%$ 的数据，保证 $1\le n \le 40000$，$1\le m \le 50000$，$1\le a_i \le 10^9$，$1 \leq l_0, r_0 \leq n$。

## 解题思路

### 问题分析

蒲公英，区间众数查询。

### 核心思路

1. 分块预处理每块之间的众数。2. 查询时暴力统计零散部分，合并块间结果。

### 算法流程

1. 读入数组并分块
2. 预处理块间众数
3. 查询

### 复杂度分析

时间 O(n * sqrt(n))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> b(a.begin() + 1, a.end());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    int sz = (int)sqrt(n), bl = (n + sz - 1) / sz;
    vector<vector<int>> cnt(bl + 1, vector<int>(b.size(), 0));
    for (int i = 1; i <= n; ++i) cnt[(i - 1) / sz][a[i]]++;
    vector<vector<int>> pre(bl + 1, vector<int>(bl + 1, 0));
    for (int i = 0; i < bl; ++i) {
        vector<int> tmp(b.size(), 0);
        for (int j = i; j < bl; ++j) {
            pre[i][j] = pre[i][j - 1];
            int best = pre[i][j - 1] > 0 ? pre[i][j - 1] : -1;
            for (int k = j * sz; k < min((j + 1) * sz, n); ++k) tmp[a[k]]++;
            if (best < 0 || tmp[a[best]] < tmp[best]) best = best;
            for (int v = 0; v < (int)b.size(); ++v)
                if (tmp[v] > (best < 0 ? 0 : tmp[best]) || (tmp[v] == (best < 0 ? 0 : tmp[best]) && v < best)) best = v;
            pre[i][j] = best >= 0 ? b[best] : 0;
        }
    }
    int last = 0;
    while (m--) {
        int l, r; cin >> l >> r;
        l = (l + last - 1) % n + 1; r = (r + last - 1) % n + 1;
        if (l > r) swap(l, r);
        int bl2 = (l - 1) / sz, br2 = (r - 1) / sz;
        int ans = -1, ansCnt = 0;
        if (bl2 == br2) {
            vector<int> tmp(b.size(), 0);
            for (int i = l; i <= r; ++i) { tmp[a[i]]++; if (tmp[a[i]] > ansCnt || (tmp[a[i]] == ansCnt && a[i] < ans)) { ans = a[i]; ansCnt = tmp[a[i]]; } }
            ans = b[ans];
        } else {
            vector<int> tmp(b.size(), 0);
            for (int i = l; i < (bl2 + 1) * sz; ++i) tmp[a[i]]++;
            for (int i = br2 * sz; i <= r; ++i) tmp[a[i]]++;
            ansCnt = 0; ans = -1;
            for (int v = 0; v < (int)b.size(); ++v)
                if (tmp[v] > ansCnt || (tmp[v] == ansCnt && v < ans)) { ans = v; ansCnt = tmp[v]; }
            if (bl2 + 1 <= br2 - 1) {
                int midans = pre[bl2 + 1][br2 - 1];
                int midv = lower_bound(b.begin(), b.end(), midans) - b.begin();
                int midcnt = 0;
                for (int i = (bl2 + 1) * sz; i < (br2) * sz; ++i) if (a[i] == midv) midcnt++;
                midcnt += tmp[midv];
                if (midcnt > ansCnt || (midcnt == ansCnt && midv < ans)) { ans = midv; ansCnt = midcnt; }
            }
            ans = b[ans];
        }
        last = ans;
        cout << ans << '\n';
    }
    return 0;
}
```
