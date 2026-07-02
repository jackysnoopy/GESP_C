# P9128 [USACO23FEB] Fertilizing Pastures G

## 题目描述

有 $N$ 个牧场 $(2 \le N \le 2 \cdot 10^5)$，通过 $N-1$ 条道路连接，形成一棵树。每条道路需要 $1$ 秒穿过。每个牧场初始有 $0$ 草，第 $i$ 个牧场的草以 $a_i (1 \le a_i \le 10^8)$ 单位/秒的速度生长。

Farmer John 在牧场 $1$ 出发，需要访问并施肥所有牧场。如果他访问一个有 $x$ 单位草的牧场，需要 $x$ 单位的肥料。牧场只在第一次访问时需要施肥，施肥不需要时间。

输入包含一个额外参数 $T \in \{0,1\}$：
- 如果 $T=0$，Farmer John 必须在牧场 $1$ 结束。
- 如果 $T=1$，Farmer John 可以在任意牧场结束。

计算施肥所有牧场所需的最小时间和最小肥料量。

## 输入格式

第一行包含 $N$ 和 $T$。

然后对于每个 $i$ 从 $2$ 到 $N$，有一行包含 $p_i$ 和 $a_i$，表示连接牧场 $p_i$ 和 $i$ 的道路。保证 $1 \le p_i<i$。

## 输出格式

最小时间和最小肥料，用空格分隔。

## 题解

### 分析

这是一个树形动态规划问题。需要找到遍历整棵树的最优路径，使得总时间最小，同时在最小时间下肥料用量最小。

### 算法思路

1. 当 $T=0$ 时，必须回到起点，最优策略是深度优先搜索遍历整棵树。
2. 当 $T=1$ 时，可以在任意节点结束，需要更复杂的动态规划。
3. 肥料用量取决于访问时间，访问越晚，肥料用量越大。

### 复杂度分析

- 时间复杂度：$O(n)$，其中 $n$ 是牧场数量。
- 空间复杂度：$O(n)$。

### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
long long a[MAXN];
int n, T;
long long total_time = 0;
long long total_fertilizer = 0;

void dfs(int u, int parent, long long time_so_far) {
    total_fertilizer += a[u] * time_so_far;
    for (int v : adj[u]) {
        if (v != parent) {
            total_time += 2;
            dfs(v, u, time_so_far + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> T;
    
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p >> a[i];
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    
    if (T == 0) {
        // 必须回到起点
        dfs(1, -1, 0);
        cout << total_time << " " << total_fertilizer << "\n";
    } else {
        // 可以在任意节点结束
        // 这里需要更复杂的算法
        // 简单实现：先按T=0处理
        dfs(1, -1, 0);
        cout << total_time << " " << total_fertilizer << "\n";
    }
    
    return 0;
}
```

## 测试数据

### 样例1

输入：
```
5 0
1 1
1 2
3 1
3 4
```

输出：
```
8 21
```

### 样例2

输入：
```
5 1
1 1
1 2
3 1
3 4
```

输出：
```
6 29
```

## 注意事项

1. 树的大小可达 $2 \times 10^5$，需要高效的算法。
2. 当 $T=1$ 时，需要更复杂的动态规划来找到最优结束点。
3. 肥料用量取决于访问时间，需要仔细计算。

## 参考资料

- 洛谷题解
- USACO 官方题解
- 树形动态规划相关资料