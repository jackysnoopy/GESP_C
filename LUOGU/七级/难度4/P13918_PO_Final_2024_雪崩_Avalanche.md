# [PO Final 2024] 雪崩 / Avalanche

## 题目描述

约书亚识破亚历山大伪造雪花照片的企图后，亚历山大变得心怀怨恨并对雪痴迷不已。他想出了一个邪恶的宏伟计划，这可能让约书亚陷入绝境，第一步就是邀请约书亚去滑雪。

他们现在身处一个大型滑雪系统，其中有 $N$ 个滑雪村庄，编号从 $1$ 到 $N$。村庄之间由 $(N-1)$ 条单向滑雪坡道连接。滑雪系统的顶部是村庄 $1$，从那里可以通过一条或多条滑雪坡道到达其他所有村庄。其余村庄都只有一条坡道通向它们。

亚历山大邪恶宏伟计划的第二步是在滑雪系统中引发雪崩。他计划通过在一个村庄制造巨大噪音来实现这一点。该村庄的雪将沿着所有源自该村庄的坡道向下崩塌。雪将尽可能地向所有方向持续向下崩塌。雪崩的破坏程度是受影响村庄的数量。

约书亚注意到亚历山大似乎心智不正常，已经看穿了他的邪恶宏伟计划。众所周知，约书亚心灵手巧，可以选择一些村庄建造围墙。在一个村庄建造围墙可以阻止雪崩到达该村庄。亚历山大不能从有围墙的滑雪村庄引发雪崩。

但时间紧迫，在警告其他滑雪者即将发生的事情后，约书亚只来得及在 $K$ 个不同的村庄建造围墙。约书亚不知道亚历山大将在哪个村庄制造噪音，但他希望将受影响的村庄数量降到最低。

首先，约书亚将建造 $K$ 道围墙，以使亚历山大能造成的最大破坏最小化。然后亚历山大将在造成最大可能破坏的村庄制造噪音。你的任务是计算破坏程度，即受雪崩影响的村庄数量。

## 输入格式

输入的第一行包含两个数字 $N$ 和 $K$（$1 \le K < N \le 10^5$），分别表示滑雪系统中的村庄数量和约书亚可以建造的围墙数量。

接下来有一行包含 $N-1$ 个数字 $a_1, a_2, ..., a_{N-1}$，其中 $1 \le a_i \le i$。对于每个 $i = 1, 2, ..., N-1$，都有一条滑雪坡道从编号为 $a_i$ 的村庄通往编号为 $i+1$ 的村庄。

## 输出格式

输出一个数字：在约书亚最优地建造围墙的情况下，亚历山大能造成的最大破坏。

## 样例

### 样例输入 1
```
5 2
1 2 1 1
```

### 样例输出 1
```
1
```

### 样例输入 2
```
7 1
1 1 2 2 3 3
```

### 样例输出 2
```
3
```

### 样例输入 3
```
7 2
1 2 2 4 1 6
```

### 样例输出 3
```
2
```

## 提示

### 子任务
**本题采用捆绑测试。**
| 子任务编号 | 得分 | 限制 |
|:-:|:-:|---|
| $1$ | $10$ | 对于所有 $1 \le i \le N-1$，有 $a_i = i$。 |
| $2$ | $10$ | $K = 1, N \le 1000$ |
| $3$ | $10$ | $N \le 20$ |
| $4$ | $15$ | $K = 1$ |
| $5$ | $25$ | $N \le 1000$ |
| $6$ | $30$ | 无额外约束。 |

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; i++) cin >> parent[i];

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++) children[parent[i]].push_back(i);

    vector<int> depth(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    depth[1] = 0;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }

    vector<int> subtree_size(n + 1, 1);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (parent[u] != 0) subtree_size[parent[u]] += subtree_size[u];
    }

    vector<int> candidates;
    for (int i = 2; i <= n; i++) {
        if (children[i].empty()) candidates.push_back(subtree_size[i]);
    }

    sort(candidates.begin(), candidates.end(), greater<int>());

    int ans = n;
    for (int i = 0; i < min(k, (int)candidates.size()); i++) {
        ans -= candidates[i];
    }

    cout << max(1, ans) << "\n";
    return 0;
}
```
