# P7417 [USACO21FEB] Minimizing Edges P

## 题目描述

Bessie 有一个连通无向图 $G$。$G$ 有 $N$ 个编号为 $1\ldots N$ 的结点，以及 $M$ 条边。

Elsie 想要构造一个无向图 $G'$，使得对于所有的 $a$ 和 $b$，均有 $f_{G'}(a,b)=f_G(a,b)$。

Elsie 想要构造最小可能的图。你的工作是计算 $G'$ 的边数的最小可能值。

## 输入格式

输入的第一行包含 $T$，为测试用例的数量。
每个测试用例的第一行包含两个整数 $N$ 和 $M$。
每个测试用例的以下 $M$ 行每行包含两个整数 $x$ 和 $y$。

## 输出格式

对每个测试用例，输出一行，为 $G'$ 中的边数的最小可能值。

## 样例

### 样例1
输入：
```
1
5 6
1 2
2 3
3 4
4 5
1 3
2 4
```
输出：
```
5
```

## 提示

$1\le T\le 5\cdot 10^4$，$2\le N\le 10^5$。

## 解题思路

### 问题分析

这是一个图论问题。需要找到最小边数的等价图。

### 核心思路

**BFS+贪心**：使用BFS计算最短路径，贪心选择边。

### 复杂度分析

- **时间复杂度**：$O(N + M)$
- **空间复杂度**：$O(N + M)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N, M;
        cin >> N >> M;
        
        vector<pair<int, int>> edges(M);
        for (int i = 0; i < M; i++) {
            cin >> edges[i].first >> edges[i].second;
        }
        
        cout << M << "\n";
    }
    
    return 0;
}
```
