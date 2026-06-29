# [USACO25OPEN] Compatible Pairs S

## 题目描述

Deep in the countryside, Farmer John’s cows aren’t just ordinary farm animals—they are part of a clandestine bovine intelligence network. Each cow carries an ID number, carefully assigned by the elite cow cryptographers. However, due to Farmer John's rather haphazard tagging system, some cows ended up with the same ID.

Farmer John noted that there are $N$ ($1\le N\le 2\cdot 10^5$) unique ID numbers, and for each unique ID $d_i$ ($0\le d_i\le 10^9$), there are $n_i$ ($1\le n_i\le 10^9$) cows who shared it.

The cows can only communicate in pairs, and their secret encryption method has one strict rule: two cows can only exchange information if they are not the same cow and the sum of their ID numbers equals either $A$ or $B$ ($0\le A\le B\le 2\cdot 10^9$). A cow can only engage in one conversation at a time (i.e., no cow can be part of more than one pair).

Farmer John would like to maximize the number of disjoint communication pairs to ensure the best information flow. Can you determine the largest number of conversations that can happen at once?

## 输入格式

The first line contains $N$, $A$, $B$.

The next $N$ lines each contain $n_i$ and $d_i$. No two $d_i$ are the same.

## 输出格式

The maximum number of disjoint communicating pairs that can be formed at the same time.

**Note that the large size of integers involved in this problem may require the use of 64-bit integer data types (e.g., a "long long" in C/C++).**

## 样例

### 样例输入 1
```
4 4 5
17 2
100 0
10 1
200 4
```

### 样例输出 1
```
118
```

### 样例输入 2
```
4 4 5
100 0
10 1
100 3
20 4
```

### 样例输出 2
```
30
```

## 提示

##### For Sample 1:

A cow with an ID of $0$ can communicate with another cow with an ID of $4$ because the sum of their IDs is $4$.  Since there are a total of $100$ cows of ID $0$ and $200$ cows of ID $4$,  there can be up to $100$ communicating pairs with this combination of IDs.

A cow with an ID of $4$ can also communicate with another cow with an ID of $1$ (sum to $5$). There are $10$ cows of ID $1$ and $100$ remaining unpaired cows of ID $4$, allowing for another $10$ pairs.

Finally, a cow with an ID of $2$ can communicate with another cow of the same ID.  Since there are a total of $17$ cows of ID $2$, there can be up to $8$ more pairs.

In total, there are $100+10+8=118$ communicating pairs. It can be shown that this is the maximum possible number of pairs.


##### For Sample 2:

Pairing IDs $0$ and $4$ makes $20$ pairs, while pairing IDs $1$ and $3$ makes $10$ pairs. It can be shown that this is the optimal pairing, resulting in a total of $30$ pairs.

#### SCORING:

- Inputs 3-4: $A=B$
- Inputs 5-7: $N\le 1000$
- Inputs 8-12: No additional constraints

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long A, B;
    cin >> N >> A >> B;

    vector<pair<long long, long long>> items(N);
    for (int i = 0; i < N; i++) {
        cin >> items[i].second >> items[i].first;
    }
    sort(items.begin(), items.end());

    vector<long long> cnt(N);
    vector<long long> id(N);
    for (int i = 0; i < N; i++) {
        id[i] = items[i].first;
        cnt[i] = items[i].second;
    }

    long long ans = 0;

    auto solve = [&](long long target) {
        if (target == 0) return;
        vector<bool> used(N, false);
        vector<pair<long long, int>> order;
        for (int i = 0; i < N; i++) order.push_back({id[i], i});
        sort(order.begin(), order.end());

        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            long long need = target - id[i];
            if (need < 0) continue;
            auto it = lower_bound(order.begin(), order.end(), make_pair(need, -1));
            if (it != order.end() && it->first == need) {
                int j = it->second;
                if (j == i) {
                    auto it2 = upper_bound(order.begin(), order.end(), make_pair(need, N));
                    if (it2 != order.end() && it2->first == need) j = it2->second;
                    else continue;
                }
                if (used[j]) continue;
                long long pairs = min(cnt[i], cnt[j]);
                if (i == j) pairs = cnt[i] / 2;
                ans += pairs;
                used[i] = true;
                used[j] = true;
            }
        }
    };

    if (A == B) {
        solve(A);
    } else {
        vector<int> order2(N);
        for (int i = 0; i < N; i++) order2[i] = i;
        sort(order2.begin(), order2.end(), [&](int x, int y) { return id[x] < id[y]; });

        vector<long long> rem = cnt;
        vector<bool> used(N, false);

        for (int i = 0; i < N; i++) {
            int idx = order2[i];
            if (used[idx]) continue;
            long long needA = A - id[idx];
            long long needB = B - id[idx];

            for (long long need : {needA, needB}) {
                if (need < 0 || need == id[idx]) continue;
                auto it = lower_bound(order2.begin() + i + 1, order2.end(), need,
                    [&](int x, long long v) { return id[x] < v; });
                if (it != order2.end() && id[*it] == need && !used[*it]) {
                    long long pairs = min(rem[idx], rem[*it]);
                    ans += pairs;
                    used[idx] = true;
                    used[*it] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            for (long long target : {A, B}) {
                long long need = target - id[i];
                if (need < 0 || need == id[i]) continue;
                auto it = lower_bound(order2.begin(), order2.end(), need,
                    [&](int x, long long v) { return id[x] < v; });
                if (it != order2.end() && id[*it] == need && !used[*it]) {
                    long long pairs = min(rem[i], rem[*it]);
                    ans += pairs;
                    used[i] = true;
                    used[*it] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            for (long long target : {A, B}) {
                if (target % 2 == 0 && id[i] == target / 2) {
                    ans += rem[i] / 2;
                    used[i] = true;
                    break;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
```

## 解题思路

### 问题分析

有 $N$ 种不同 ID 的牛，每种有 $n_i$ 头。两头牛可以配对当且仅当它们的 ID 之和等于 $A$ 或 $B$。求最大配对数。

### 核心思路

分类讨论：当 $A = B$ 时，直接处理单目标配对；当 $A \neq B$ 时，优先处理 ID 较小的配对（优先配对 $A$ 目标），再处理剩余的。对于相同 ID 配对，取 $\lfloor n/2 \rfloor$。

**关键观察**：配对是互斥的，每头牛最多参与一次。贪心地按 ID 从小到大处理，优先匹配较小的目标值。

### 算法流程

1. 读入所有 ID 和数量，按 ID 排序。
2. 若 $A = B$，直接处理单目标配对。
3. 若 $A \neq B$，分两轮处理：先优先配对 $A$ 目标，再处理 $B$ 目标。
4. 最后处理相同 ID 的自配对。
5. 输出总配对数。

### 复杂度分析

- 时间复杂度：$O(N \log N)$，排序和二分查找。
- 空间复杂度：$O(N)$，存储 ID 和数量。
