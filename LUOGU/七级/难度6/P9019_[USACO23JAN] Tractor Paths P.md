# [USACO23JAN] Tractor Paths P

## 题目描述
Farmer John has $N$ tractors, where the $i$-th tractor can only be used within the inclusive interval $[l_i,r_i]$. The tractor intervals have left endpoints $l_1<l_2<\cdots <l_N$ and right endpoints $r_1<r_2< \cdots <r_N$. Some of the tractors are special.

Two tractors $i$ and $j$ are said to be adjacent if $[l_i,r_i]$ and $[l_j,r_j]$ intersect. Farmer John can transfer from one tractor to any adjacent tractor.

You are given $Q$ queries, each specifying a pair of tractors $a$ and $b$. For each query, output two integers:
- The length of any shortest path between tractor $a$ to tractor $b$.
- The number of special tractors such that there exists at least one shortest path from tractor $a$ to tractor $b$ containing it.

## 输入格式
The first line contains $N$ and $Q$.

The next line contains a string of length $2N$ consisting of Ls and Rs, representing the left and right endpoints in sorted order.

The next line contains a bit string of length $N$, representing for each tractor whether it is special or not.

The next $Q$ lines each contain two integers $a$ and $b$, specifying a query.

## 输出格式
For each query, the two quantities separated by spaces.

## 样例
### 样例1
输入:
```
8 10
LLLLLRRRRRRRRR
11011010
1 2
1 3
1 4
1 5
1 6
1 7
1 8
2 3
2 4
2 5
```
输出:
```
1 2
1 3
1 4
2 4
2 4
2 5
2 5
1 2
2 3
2 4
```

## 提示
- 时间限制：4000ms
- 内存限制：524288KB

## 解题思路

### 问题分析
需要计算区间图上两点间的最短路径长度和特殊节点数量。

### 核心思路
1. 使用BFS计算最短路径
2. 统计特殊节点

### 算法流程
1. 解析区间
2. 对于每个查询，使用BFS
3. 统计结果

### 复杂度分析
- 时间复杂度：$O(Q \cdot N)$
- 空间复杂度：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int l[MAXN], r[MAXN];
bool special[MAXN];
int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> q;
    
    string lr;
    cin >> lr;
    
    string spec;
    cin >> spec;
    
    vector<int> stack;
    int idx = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (lr[i] == 'L') {
            stack.push_back(idx);
            l[idx] = i + 1;
            idx++;
        } else {
            int pos = stack.back();
            stack.pop_back();
            r[pos] = i + 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        special[i] = (spec[i] == '1');
    }
    
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        
        vector<int> dist(n, -1);
        dist[a] = 0;
        
        vector<int> queue;
        queue.push_back(a);
        
        int head = 0;
        while (head < queue.size()) {
            int u = queue[head++];
            
            for (int v = 0; v < n; v++) {
                if (dist[v] == -1 && !(r[u] < l[v] || r[v] < l[u])) {
                    dist[v] = dist[u] + 1;
                    queue.push_back(v);
                }
            }
        }
        
        int shortest = dist[b];
        
        int special_count = 0;
        for (int v = 0; v < n; v++) {
            if (special[v] && dist[v] <= shortest) {
                if (dist[v] + dist[v] <= shortest) {
                    special_count++;
                }
            }
        }
        
        cout << shortest << " " << special_count << "\n";
    }
    
    return 0;
}
```