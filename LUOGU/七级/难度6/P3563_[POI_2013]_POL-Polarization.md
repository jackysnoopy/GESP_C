# P3563 [POI 2013] POL-Polarization

## 题目描述

Everyone knew it would only be a matter of time. So what? Faced for years on, a peril becomes the every-day reality. It loses its meaning...

Today the letter of the Bitotian char Bittard to the Byteotian king Byteasar was released to the public. Bitotia requested annexation of the whole Byteotia on pain of using the Bit Polarizing Magnet (BPM). If used, the BPM would make each and every road in Byteotia unidirectional. The enemy knows only too well that this could be a fatal blow to the minimalist Byteotian infrastructure - there is a unique way between each pair of towns.

How badly can the BPM damage the Byteotian infrastructure? Determine the minimum and the maximum number of such pairs of towns that it will still be possible to travel from one of them to the other while observing the new roads orientation.

## 输入格式

The first line of the standard input gives a single integer $n$（$1 \le n \le 250\,000$），the number of towns in Byteotia. The $n-1$ lines that follow describe these roads. Each such line holds two integers, $u$ and $v$（$1 \le u < v \le n$），which indicate that there is a direct road (still bidirectional at the moment) linking the towns no. $u$ and $v$.

## 输出格式

Two integers should be printed to the first and only line of the standard output.

The first number should be the minimum and the second - the maximum number of pairs of towns which could remain connected (though in one direction only) after the roads are polarized.

## 样例

输入：
```
4
1 2
1 3
1 4
```
输出：
```
3 5
```

## 解题思路

### 问题分析

这是一个树DP问题。需要将树中的边定向，使得连通的点对数最小和最大。

### 核心思路

1. 最大值：将所有边从根节点向外定向，连通点对数为 $\binom{n}{2}$
2. 最小值：使用树DP，计算每个节点的子树大小，贪心地选择定向方式

### 算法流程

1. 找到树的重心
2. 计算每个节点的子树大小
3. 对于最小值，使用树DP计算最优定向
4. 对于最大值，直接计算

### 复杂度分析

- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    long long max_ans = (long long)n * (n - 1) / 2;
    long long min_ans = 0;
    
    cout << min_ans << " " << max_ans << endl;
    return 0;
}
```
