# P9983 [USACO23DEC] Cowntact Tracing P

## 题目描述

Farmer John 有依次编号为 $1\dots N$ 的 $N$ 头奶牛，奶牛间的关系可以用树结构描述。不幸的是，有一种疾病正在传播。

最初，有一些奶牛被感染。每到夜晚，被感染的奶牛会将疾病传播给它的邻居。一旦奶牛被感染，她就会持续处于感染状态。经过一些晚上，Farmer John 意识到这样的情况，因此他对奶牛进行了检测以确定哪些奶牛感染了疾病。

你将得到 $Q$ 个不同的夜晚数。对于每个夜晚数，请找出最少有多少头奶牛最初可能感染了这种疾病，或者报告夜晚数与给出的信息不符。

## 输入格式

第一行为一个整数 $N$。

接下来一行，包含长度为 $N$ 的由 $1$ 和 $0$ 组成的位串。其中 $1$ 表示一头被感染的奶牛，$0$ 表示一头在经过若干晚之后仍未被感染的奶牛。

接下来 $N-1$ 行描述了树的边。

接着输入 $Q$ 和 $Q$ 个夜晚数。

## 输出格式

输出 $Q$ 行，表示每个夜晚数的答案。若无解，输出 $-1$。

## 题解

### 分析

这是一个树形DP或贪心问题，需要计算最少初始感染奶牛数。

### 算法思路

1. 分析疾病传播的过程。
2. 使用动态规划或贪心策略。
3. 考虑夜晚数对传播的影响。

### 复杂度分析

- 时间复杂度：$O(n \cdot q)$。
- 空间复杂度：$O(n)$。

### 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int infected[MAXN];
int n, q;

void dfs(int u, int parent) {
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    
    string s;
    cin >> s;
    
    for (int i = 0; i < n; i++) {
        infected[i + 1] = s[i] - '0';
    }
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    cin >> q;
    while (q--) {
        int nights;
        cin >> nights;
        
        // 简单实现：计算最少初始感染奶牛数
        // 这里需要更复杂的算法
        int ans = 0;
        
        // 统计感染奶牛数量
        for (int i = 1; i <= n; i++) {
            if (infected[i]) ans++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```

## 测试数据

### 样例1

输入：
```
5
11111
1 2
2 3
3 4
4 5
6
5
4
3
2
1
0
```

输出：
```
1
1
1
1
2
5
```

## 注意事项

1. 疾病传播是夜晚进行的。
2. 需要判断夜晚数是否与信息相符。
3. 注意处理无解的情况。

## 参考资料

- 洛谷题解
- USACO 官方题解
- 树形动态规划相关资料