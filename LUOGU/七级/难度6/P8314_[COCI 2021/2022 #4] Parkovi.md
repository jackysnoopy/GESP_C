# [COCI 2021/2022 #4] Parkovi

## 题目描述
这个城市由 $n$ 个社区组成，社区间由 $n-1$ 条道路连接。并且从任意一个社区出发，可以到任意一个社区去。一共会建造 $k$ 座公园，同一个社区内只会存在一座公园。市政府希望尽可能减小从每个社区到最近公园的距离的最大值。

帮助政府应该在那些社区建造公园，可以使每个社区到最近公园的距离的最大值最小。

## 输入格式
第一行包含两个整数 $n,k$，分别表示社区数目和需要建造的公园数目。

接下来 $n-1$ 行，第 $i$ 行包含三个数 $a_i,b_i,w_i$，分别表示有一条长度为 $w_i$ 道路连接着社区 $a_i,b_i$。

## 输出格式
第一行包含一个整数，即每个社区到最近公园的距离的最大值的最小值。

第二行包含 $k$ 个整数，可以使每个社区到最近公园的距离的最大值最小所需要修建的公园所在的社区编号。

## 样例
### 样例1
输入:
```
9 3
1 2 5
1 3 1
3 4 10
3 5 9
5 6 8
2 7 1
2 8 2
8 9 7
```
输出:
```
8
4 5 8
```

### 样例2
输入:
```
5 2
1 2 3
2 3 7
3 4 3
4 5 3
```
输出:
```
3
2 4
```

## 提示
- 时间限制：3000ms
- 内存限制：512000KB

## 解题思路

### 问题分析
需要在树上选择 $k$ 个点作为公园，使得所有点到最近公园的最大距离最小。

### 核心思路
1. 二分答案
2. 使用贪心或DP检查是否可行

### 算法流程
1. 二分最大距离
2. 使用贪心选择公园位置
3. 验证是否覆盖所有点

### 复杂度分析
- 时间复杂度：$O(n \log R)$
- 空间复杂度：$O(n)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 200005;
vector<pair<int, int>> adj[MAXN];
int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    
    int low = 0, high = 1e9;
    
    while (low < high) {
        int mid = (low + high) / 2;
        
        int centers = 0;
        vector<bool> covered(n + 1, false);
        
        for (int i = 1; i <= n; i++) {
            if (!covered[i]) {
                centers++;
                queue<pair<int, int>> q;
                q.push({i, 0});
                covered[i] = true;
                
                while (!q.empty()) {
                    auto [u, dist] = q.front();
                    q.pop();
                    
                    if (dist >= mid) continue;
                    
                    for (auto [v, w] : adj[u]) {
                        if (!covered[v]) {
                            covered[v] = true;
                            q.push({v, dist + w});
                        }
                    }
                }
            }
        }
        
        if (centers <= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    cout << low << endl;
    
    vector<int> centers;
    vector<bool> covered(n + 1, false);
    
    for (int i = 1; i <= n && centers.size() < k; i++) {
        if (!covered[i]) {
            centers.push_back(i);
            queue<pair<int, int>> q;
            q.push({i, 0});
            covered[i] = true;
            
            while (!q.empty()) {
                auto [u, dist] = q.front();
                q.pop();
                
                if (dist >= low) continue;
                
                for (auto [v, w] : adj[u]) {
                    if (!covered[v]) {
                        covered[v] = true;
                        q.push({v, dist + w});
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < centers.size(); i++) {
        cout << centers[i] << (i + 1 == centers.size() ? "\n" : " ");
    }
    
    return 0;
}
```