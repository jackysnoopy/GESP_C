# Color a Tree

## 题目描述

给定一棵有 n 个节点的树，每个节点有一个花费 cost。需要将所有节点染色，每次可以选择一个未染色的节点进行染色，花费为该节点的 cost。但有一个特殊规则：如果一个节点被染色，那么它的所有父节点（直到根）必须已经被染色。求将所有节点染色的最小总花费。

## 输入格式

- 多组测试数据，每组第一行两个整数 n 和 root
- 接下来 n 个整数，表示每个节点的花费
- 接下来 n-1 行，每行两个整数 a 和 b，表示 b 是 a 的子节点
- 输入以 "0 0" 结束

## 输出格式

每组数据输出一个整数，表示最小总花费

## 样例

```
输入：
3 1
10 20 30
1 2
1 3
0 0

输出：
80
```

## 提示

- 贪心策略：每次选择平均花费最大的非根节点合并到其父节点
- 合并时需要更新父节点的花费、节点数和平均花费

## 解题思路

### 问题分析

染色顺序受限于父子关系，需要找到最优的合并顺序来最小化总花费。

### 核心思路

贪心策略：每次选择平均花费（cost/节点数）最大的非根节点，将其合并到父节点。合并时，父节点需要额外花费该子树的总花费 × 当前已合并的节点数。

### 算法流程

1. 初始化每个节点的 cost、cnt=1、avg=cost
2. 重复 n-1 次：
   - 找到平均花费最大的非根节点 best
   - 将 best 合并到其父节点 p：
     - total += best.cost × p.cnt
     - p.cnt += best.cnt
     - p.cost += best.cost
     - p.avg = p.cost / p.cnt
   - 将 best 的子节点重新挂在 p 下
   - 标记 best 为已合并
3. 输出 total

### 复杂度分析

- 时间复杂度：O(n²)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Node {
    int cost, cnt, parent;
    double avg;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n, root;
        cin >> n >> root;
        if (n == 0 && root == 0) break;
        
        vector<Node> nodes(n + 1);
        long long total = 0;
        for (int i = 1; i <= n; i++) {
            cin >> nodes[i].cost;
            nodes[i].cnt = 1;
            nodes[i].avg = nodes[i].cost;
            total += nodes[i].cost;
        }
        
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            nodes[b].parent = a;
        }
        
        for (int iter = 1; iter < n; iter++) {
            int best = -1;
            double best_avg = -1;
            for (int i = 1; i <= n; i++) {
                if (i != root && nodes[i].parent != 0 && nodes[i].avg > best_avg) {
                    best_avg = nodes[i].avg;
                    best = i;
                }
            }
            
            if (best == -1) break;
            
            int p = nodes[best].parent;
            total += nodes[best].cost * nodes[p].cnt;
            nodes[p].cnt += nodes[best].cnt;
            nodes[p].cost += nodes[best].cost;
            nodes[p].avg = (double)nodes[p].cost / nodes[p].cnt;
            
            for (int i = 1; i <= n; i++)
                if (nodes[i].parent == best)
                    nodes[i].parent = p;
            
            nodes[best].parent = 0;
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
```
