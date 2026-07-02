# [GCJ 2014 #1B] The Bored Traveling Salesman

## 题目描述

给定 N 个城市和双向航班，需要设计一条旅行路线，按首次访问顺序拼接各城市 5 位 ZIP 编码，使得拼接结果最小。

## 输入格式

第一行 T，每组包含 N、M，N 个 ZIP 编码，M 条边。

## 输出格式

Case #x: y，y 为最小的拼接数字。

## 样例

```
4
3 2
10001
20000
10000
1 2
2 3
...
```

输出：
```
Case #1: 100002000010001
```

## 解题思路

### 问题分析
需要找到一个访问城市顺序，使得按该顺序拼接 ZIP 编码后的数字最小。关键约束是每次"出站"航班到一个城市后，最终必须"返回"。

### 核心思路
- 按 ZIP 编码排序城市
- 从 ZIP 最小的城市开始，BFS 遍历邻接图
- 优先访问 ZIP 较小的邻居城市

### 算法流程
1. 将城市按 ZIP 排序
2. 从 ZIP 最小城市开始 BFS
3. 拼接访问顺序的 ZIP 编码

### 复杂度分析
- 时间：O(N log N + M)
- 空间：O(N + M)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, M; cin >> N >> M;
        vector<string> zip(N);
        for (int i = 0; i < N; i++) cin >> zip[i];
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; i++) {
            int u, v; cin >> u >> v; u--; v--;
            adj[u].push_back(v); adj[v].push_back(u);
        }
        vector<int> cityOrder(N);
        for (int i = 0; i < N; i++) cityOrder[i] = i;
        sort(cityOrder.begin(), cityOrder.end(), [&](int a, int b) { return zip[a] < zip[b]; });
        vector<bool> visited(N, false);
        vector<int> result;
        for (int s : cityOrder) {
            if (visited[s]) continue;
            vector<int> queue = {s}; visited[s] = true;
            int head = 0;
            while (head < (int)queue.size()) {
                int u = queue[head++];
                result.push_back(u);
                vector<int> nb;
                for (int v : adj[u]) if (!visited[v]) { visited[v] = true; nb.push_back(v); }
                sort(nb.begin(), nb.end(), [&](int a, int b) { return zip[a] < zip[b]; });
                for (int v : nb) queue.push_back(v);
            }
        }
        cout << "Case #" << t << ": ";
        for (int i = 0; i < N; i++) cout << zip[result[i]];
        cout << "\n";
    }
    return 0;
}
```
