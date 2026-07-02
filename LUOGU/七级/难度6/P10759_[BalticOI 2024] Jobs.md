# [BalticOI 2024] Jobs

## 题目描述

有 N 个一次性工作，完成第 i 个工作将给你带来 xi 欧元的利润。有些工作依赖于另一个工作。你目前有 s 欧元，可以决定做哪些工作以及以什么顺序去做，只要尊重依赖关系，且钱数不能变成负数。求最大利润。

## 输入格式

第一行包含两个整数 N 和 s。
接下来的 N 行，每行包含两个整数 x 和 p，分别是第 i 个工作的利润和它所依赖的前置工作的编号。

## 输出格式

输出一个整数，即你能够获得的最大利润。

## 样例

### 样例 1
输入：
```
6 1
3 0
-3 1
-5 0
2 1
6 3
-4 5
```
输出：
```
6
```

## 提示

对于 100% 的数据，1≤N≤3×10^5，0≤s≤10^18，-10^9≤xi≤10^9，0≤pi<i。

## 解题思路

### 问题分析
需要在满足依赖关系和资金约束下最大化利润。

### 核心思路
拓扑排序 + 贪心，优先选择利润高的工作。

### 算法流程
1. 构建依赖图
2. 拓扑排序
3. 使用优先队列选择利润最高的可执行工作
4. 检查资金约束

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 300005;
int n;
long long s;
long long x[MAXN];
int p[MAXN];
vector<int> children[MAXN];
int indegree[MAXN];

int main() {
    scanf("%d %lld", &n, &s);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld %d", &x[i], &p[i]);
        if (p[i] != 0) {
            children[p[i]].push_back(i);
            indegree[i]++;
        }
    }
    
    priority_queue<pair<long long, int>> pq;
    vector<bool> done(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push({x[i], i});
        }
    }
    
    long long ans = 0;
    long long money = s;
    
    while (!pq.empty()) {
        auto [profit, u] = pq.top();
        pq.pop();
        
        if (done[u]) continue;
        done[u] = true;
        
        if (money + profit >= 0) {
            money += profit;
            ans += profit;
        }
        
        for (int v : children[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push({x[v], v});
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}
```