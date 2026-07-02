# P6142 [USACO20FEB] Delegation P

## 题目大意

给定一棵 N 个节点的树，将所有边划分成若干条链，每条链的长度（边数）至少为 K。求最大的 K。

## 解题思路

### 二分答案

由于答案具有单调性（如果 K 可行，那么所有小于 K 的值也可行），可以二分答案。

### 树形 DP 判定

对于给定的 K，判断是否可以将树划分成长度 >= K 的链：

1. **DFS 遍历树**：从叶子节点向上处理
2. **收集子链**：每个节点从子节点获得"未匹配的链长度"
3. **贪心配对**：将子链排序后，用双指针贪心配对，使配对数最多
   - 如果两个链长度之和 >= K，可以合并成一条完整路径
   - 剩余未配对的最长链向上延伸 1（加上当前边）
4. **根节点检查**：根节点不能有未配对的链（否则无法形成完整路径）

### 关键观察

- 叶子节点返回 0（没有子链）
- 非叶子节点：收集所有子节点的返回值，排序后贪心配对
- 如果某个节点有未配对的链，返回 `max_unpaired + 1`（延伸到父节点）
- 如果所有链都配对成功，返回 0

### 复杂度

- 二分 O(log N)
- 每次判定 O(N log N)（排序）
- 总复杂度：O(N log²N)

## 代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int n;
vector<int> adj[MAXN];
int K;
bool ok;

int dfs(int u, int parent) {
    vector<int> chains;
    for (int v : adj[u]) {
        if (v == parent) continue;
        int d = dfs(v, u);
        if (!ok) return 0;
        chains.push_back(d);
    }

    if (chains.empty()) {
        return 0;
    }

    sort(chains.begin(), chains.end());

    int left = 0, right = (int)chains.size() - 1;
    int max_unpaired = 0;
    vector<bool> used(chains.size(), false);

    while (left < right) {
        if (chains[left] + chains[right] >= K) {
            used[left] = used[right] = true;
            left++;
            right--;
        } else {
            left++;
        }
    }

    for (int i = 0; i < (int)chains.size(); i++) {
        if (!used[i]) {
            max_unpaired = max(max_unpaired, chains[i]);
        }
    }

    if (u == 1 && max_unpaired > 0) {
        ok = false;
        return 0;
    }

    return max_unpaired + 1;
}

bool check(int k) {
    K = k;
    ok = true;
    dfs(1, 0);
    return ok;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int lo = 1, hi = n - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    printf("%d\n", lo);
    return 0;
}
```

## 测试样例

输入：
```
8
1 2
1 3
1 4
2 5
2 6
3 7
3 8
```

输出：
```
3
```
