# [GCJ 2014 #1B] The Bored Traveling Salesman

## 题目描述

N 个城市，每个有 5 位 ZIP 码。需要访问所有城市，每次出发和返回构成一张票。求首次访问城市时 ZIP 码拼接的最小值。

## 输入格式

第一行 T。
每个用例第一行 N, M。
接下来 N 行是 ZIP 码。
接下来 M 行是航线。

## 输出格式

输出 Case #x: y。

## 样例

### 样例 1
输入：
```
4
3 2
10001
20000
10000
1 2
2 3
5 4
36642
28444
50012
29651
10953
1 4
2 3
2 5
4 5
5 5
36642
28444
50012
29651
10953
1 2
1 4
2 3
2 5
4 5
6 6
10001
10002
10003
10004
10005
10006
1 2
1 6
2 3
2 4
3 5
4 5
```
输出：
```
Case #1: 100002000010001
Case #2: 1095328444500122965136642
Case #3: 1095328444366422965150012
Case #4: 100011000210003100041000510006
```

## 提示

- 1 ≤ N ≤ 50

## 解题思路

### 问题分析

需要找到访问所有城市的顺序，使得 ZIP 码拼接最小。

### 核心思路

1. 从最小 ZIP 码开始
2. 贪心访问可达的最小 ZIP 码
3. 使用 BFS/DFS

### 算法流程

1. 构建图
2. 贪心选择下一个城市
3. 拼接 ZIP 码

### 复杂度分析

- 时间复杂度：O(N^2)
- 空间复杂度：O(N + M)

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
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;
        
        vector<string> zip(N);
        for (int i = 0; i < N; i++) cin >> zip[i];
        
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<bool> visited(N, false);
        string ans;
        
        int start = 0;
        for (int i = 1; i < N; i++) {
            if (zip[i] < zip[start]) start = i;
        }
        
        visited[start] = true;
        ans = zip[start];
        
        for (int step = 1; step < N; step++) {
            int next = -1;
            for (int i = 0; i < N; i++) {
                if (!visited[i]) {
                    bool reachable = false;
                    for (int v : adj[i]) {
                        if (visited[v]) { reachable = true; break; }
                    }
                    if (reachable && (next == -1 || zip[i] < zip[next])) next = i;
                }
            }
            if (next != -1) {
                visited[next] = true;
                ans += zip[next];
            }
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    return 0;
}
```
