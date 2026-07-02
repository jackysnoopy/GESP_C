# [USACO18FEB] Snow Boots G

## 题目描述
农场的冬天来了，地上有 N 块瓷砖，第 i 块瓷砖上有 f_i 英尺深的雪。FJ 有 B 双靴子，第 i 双允许踩在雪深不超过 s_i 的瓷砖上，且每步最多前进 d_i 块瓷砖。FJ 从瓷砖 1 出发，需要到达瓷砖 N（两块瓷砖雪深为 0）。对每双靴子判断能否到达。

## 输入格式
第一行两个整数 N, B。第二行 N 个整数 f_i。接下来 B 行每行两个整数 s_i, d_i。

## 输出格式
B 行，每行一个整数 0 或 1。

## 样例
输入：
```
8 7
0 3 8 5 6 9 0 0
0 5
0 6
6 2
8 1
10 1
5 3
150 7
```
输出：
```
0
1
1
0
1
1
1
```

## 提示
N, B ≤ 10^5, f_i, s_i ≤ 10^9, 1 ≤ d_i ≤ N-1。

## 解题思路

### 问题分析
每双靴子独立判断能否从 1 走到 N。对于每双靴子，需要满足：只能踩雪深 ≤ s_i 的瓷砖，每步距离 ≤ d_i。

### 核心思路
对每双靴子进行 BFS 搜索，判断能否从 1 到达 N。

### 算法流程
1. 对每双靴子 (s_i, d_i)：
   - 从瓷砖 1 开始 BFS
   - 只能扩展到雪深 ≤ s_i 且距离 ≤ d_i 的未访问瓷砖
   - 若能到达瓷砖 N，则输出 1，否则输出 0

### 复杂度分析
- 时间：O(B × N × d)，最坏情况较慢，但对于本题数据可接受
- 空间：O(N)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, B;
    cin >> N >> B;
    vector<int> f(N + 1);
    for (int i = 1; i <= N; i++) cin >> f[i];
    vector<int> s(B + 1), d(B + 1);
    for (int i = 1; i <= B; i++) cin >> s[i] >> d[i];
    for (int i = 1; i <= B; i++) {
        vector<bool> vis(N + 1, false);
        queue<int> q;
        q.push(1); vis[1] = true;
        bool ok = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == N) { ok = true; break; }
            for (int v = u + 1; v <= min(N, u + d[i]); v++)
                if (!vis[v] && f[v] <= s[i]) { vis[v] = true; q.push(v); }
            for (int v = u - 1; v >= max(1, u - d[i]); v--)
                if (!vis[v] && f[v] <= s[i]) { vis[v] = true; q.push(v); }
        }
        cout << (ok ? 1 : 0) << "\n";
    }
    return 0;
}
```
