# [JOIST 2024] 逃生路线 2 / Escape Route 2

## 题目描述

IOI 王国由从西向东排列的 N 座城市组成。JOI 组织成员只能使用 JOY 航空公司运营的航班进行城市间旅行。每趟航班每天从城市 i 在时间 Ai,j 起飞，于当天的时间 Bi,j 到达城市 i+1。JOI 组织有 Q 名成员，每名成员想知道从城市 Lk 出发到城市 Rk 的最短时间。

## 输入格式

- N T
- M1
- A1,1 B1,1
- A1,2 B1,2
- ...
- M2
- ...
- Q
- L1 R1
- L2 R2
- ...

## 输出格式

输出 Q 行，第 k 行输出成员 k 从城市 Lk 到城市 Rk 所需的最短时间。

## 样例

### 样例 1
输入：
```
4 10000
1
100 300
2
200 400
300 600
1
500 600
3
1 3
2 4
1 4
```
输出：
```
500
400
10500
```

## 提示

对于 100% 的数据：2≤N≤100,000，2≤T≤10^9，Mi≥1，ΣMi≤100,000，1≤Q≤300,000。

## 解题思路

### 问题分析
需要计算从一个城市到另一个城市的最短时间，考虑航班时刻表和等待时间。

### 核心思路
使用 Dijkstra 算法，考虑航班的等待时间和飞行时间。

### 算法流程
1. 将航班信息存储为图
2. 使用优先队列优化的 Dijkstra 算法
3. 计算每个查询的最短时间

### 复杂度分析
- 时间复杂度：O((N + ΣMi) log N + Q log N)
- 空间复杂度：O(N + ΣMi)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 100005;
const long long INF = 1e18;

struct Flight {
    int a, b;
};

int main() {
    int N, T;
    scanf("%d %d", &N, &T);
    
    vector<vector<Flight>> flights(N);
    for (int i = 0; i < N - 1; i++) {
        int M;
        scanf("%d", &M);
        flights[i].resize(M);
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &flights[i][j].a, &flights[i][j].b);
        }
    }
    
    int Q;
    scanf("%d", &Q);
    
    for (int i = 0; i < Q; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        L--; R--;
        
        vector<long long> dist(N, INF);
        dist[L] = 0;
        
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, L});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            if (u == R) break;
            
            for (auto& f : flights[u]) {
                int v = u + 1;
                long long new_dist = d;
                
                if (new_dist % T <= f.a) {
                    new_dist += f.a - (new_dist % T);
                } else {
                    new_dist += T - (new_dist % T) + f.a;
                }
                
                new_dist += f.b - f.a;
                
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pq.push({new_dist, v});
                }
            }
        }
        
        printf("%lld\n", dist[R]);
    }
    
    return 0;
}
```