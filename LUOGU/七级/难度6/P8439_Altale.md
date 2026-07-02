# Altale (Fan-made FTR 7)

## 题目描述
小机器人又在钓星星了。

星星在天空中形成了若干个星座，每个星座有一个"中心点"，如果星星脱离了与中心点的直接或间接的联系，那么星星就会从星座中脱离，掉落到地面上。

经过小机器人日日夜夜的观测，他发现了这些星座的性质：每一个星座内部都是联通的，星星的联系的数量总与星座中星星的数量相等。

另外，不同的星座之间星星没有联系，同一个星座中的星星都有间接或直接的联系。

他通过观测天体运动给星星编了号，他发现每个星座的中心点都是星座中编号最小的星星。

可惜的是，小机器人只能通过随（diao）缘（yu）的方式获得取消这些联系的钥匙。

小机器人非常贪心，想要用尽量少的时间获得尽量多的星星。

他想要 $k$ 颗星星，你能告诉他他至少需要钓上几把钥匙吗？

## 输入格式
第一行两个整数 $n,k$，表示天空中所有的星星的总数和星星之间联系总数，和小机器人希望获得的星星数。

接下来 $n$ 行，每行两个整数 $u,v$ 表示第 $u$ 颗和第 $v$ 颗星星之间存在联系。

保证任意星座内星星联系条数等于星星数，星星不会有自己到自己的联系，不会有两条联系建立在同样两颗星星上。

## 输出格式
一行一个整数，表示小机器人需要获得足够的星星所需最少的钥匙数。

## 样例
### 样例1
输入:
```
4 1
1 2
2 3
3 1
1 4
```
输出:
```
1
```

### 样例2
输入:
```
17 9
1 2
1 6
1 3
3 4
4 5
5 6
6 7
8 10
10 9
10 11
11 12
11 13
13 14
14 8
15 13
8 16
16 17
```
输出:
```
3
```

## 提示
- 时间限制：1000ms
- 内存限制：262144KB

## 解题思路

### 问题分析
每个星座是一个基环树（n个节点n条边），需要通过移除边来获得星星。

### 核心思路
1. 识别每个星座（连通分量）
2. 每个星座可以提供若干星星
3. 贪心选择最优的移除方案

### 算法流程
1. 使用并查集或DFS识别星座
2. 计算每个星座能提供的星星数
3. 贪心选择需要移除的边数

### 复杂度分析
- 时间复杂度：$O(n \alpha(n))$
- 空间复杂度：$O(n)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000005;
vector<int> adj[MAXN];
bool visited[MAXN];
int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int components = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            components++;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    
    cout << max(0, k - components) << endl;
    
    return 0;
}
```