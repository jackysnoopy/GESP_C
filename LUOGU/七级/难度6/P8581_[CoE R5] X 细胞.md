# [CoE R5] X 细胞

## 题目描述
X 细胞是来自于仙女座星系 Gamma 行星的一种古老生命形式。

初始时，只有 1 个 X 细胞，而 X 细胞可以通过直接分裂来产生后代 X 细胞。

每个 X 细胞具有活力值 $h_x$ 和体积 $v_x$，变异指数 $d_x = \frac{h_x}{v_x}$。

当 X 细胞受到特定的外界刺激后，它会激活并开始同化过程来转变为一个 Z 细胞。

在同化过程中，Y 细胞会遵循以下原则：
- 如果某个子细胞 $j$ 的母细胞 $i$ 尚未被同化，则该子细胞 $j$ 不会被同化。
- 能够使得 Y 细胞变异指数尽可能地小且同化尽可能多的细胞。

## 输入格式
输入的第一行是一个整数 $n$，表示 X 细胞的数量。

接下来的一行，包含 $n - 1$ 个整数，依次表示编号为 $2 \sim n$ 的 X 细胞的母细胞的编号。

接下来的一行，包含 $n$ 个整数，依次表示编号为 $i$ 的 X 细胞的活力值 $h_i$。

再接下来的一行，包含 $n$ 个整数，依次表示编号为 $i$ 的 X 细胞的体积 $v_i$。

## 输出格式
输出一个整数，表示使得所有 X 细胞均转变为 Z 细胞所需消耗的激活剂数量的最少值。

## 样例
### 样例1
输入:
```
3
1 2
5 7 12
1 1 10
```
输出:
```
2
```

### 样例2
输入:
```
3
1 1
2 2 12
2 3 4
```
输出:
```
9
```

## 提示
- 时间限制：1000-3000ms
- 内存限制：262144-327680KB

## 解题思路

### 问题分析
需要在树上选择激活顺序，使得总激活剂消耗最少。

### 核心思路
1. 使用贪心策略，优先激活变异指数小的子树
2. 计算每个子树的最优激活方案

### 算法流程
1. DFS遍历树，计算每个子树的信息
2. 贪心选择激活顺序
3. 计算总消耗

### 复杂度分析
- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 1000005;
int h[MAXN], v[MAXN];
int parent[MAXN];
vector<int> children[MAXN];
int n;

void dfs(int u) {
    for (int child : children[u]) {
        dfs(child);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        children[parent[i]].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    
    long long ans = 0;
    int step = 1;
    
    vector<int> order;
    vector<int> in_degree(n + 1, 0);
    
    for (int i = 2; i <= n; i++) {
        in_degree[i]++;
    }
    
    vector<int> queue;
    queue.push_back(1);
    
    while (!queue.empty()) {
        int u = queue.front();
        queue.erase(queue.begin());
        order.push_back(u);
        
        for (int v : children[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                queue.push_back(v);
            }
        }
    }
    
    for (int u : order) {
        if (u == 1) continue;
        
        long long total_h = h[u];
        long long total_v = v[u];
        
        for (int child : children[u]) {
            total_h += h[child];
            total_v += v[child];
        }
        
        long long ratio = (total_h + total_v - 1) / total_v;
        ans += step * ratio;
        step++;
    }
    
    cout << ans << endl;
    
    return 0;
}
```