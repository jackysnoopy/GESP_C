# Color a Tree

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3646

[PDF](https://uva.onlinejudge.org/external/12/p1205.pdf)

## 输入格式
（无输入格式）

## 输出格式
（无输出格式）

## 样例
### 样例 1
```
5 1
1 2 1 2 4
1 2
1 3
2 4
3 5
0 0
```
```
33
```

## 解题思路

### 问题分析
一棵树每个节点有染色代价。染色一个节点前必须先染其父节点。求最小总染色时间（时间从 1 开始递增）。

### 核心思路
贪心：每次选择平均代价最大的节点（除根外）进行染色。用并查集合并节点。

### 算法流程
1. 读入 n 和根节点 r
2. 读入每个节点的代价
3. 用并查集维护已合并的节点集合
4. 每次找平均代价最大的非根节点，合并到父节点
5. 总代价 += 子节点代价 × 父节点已有节点数
6. 输出结果

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
            // 找平均代价最大的非根节点
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
            
            // 将 best 的子节点挂在 p 下
            for (int i = 1; i <= n; i++)
                if (nodes[i].parent == best)
                    nodes[i].parent = p;
            
            nodes[best].parent = 0; // 标记已合并
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
```
