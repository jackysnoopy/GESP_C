# P10647 [NordicOI 2023] Ice Cream Machines

## 思路

核心算法：Belady算法（贪心+集合）

经典的缓存替换策略：当需要淘汰时，选择下次使用最远（或不再使用）的口味。用 set 维护当前机器中的口味及其下次使用位置，用 map 快速查找和更新。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<int> next_pos(m + 1, n);
    vector<int> next_occ(n);
    for (int i = n - 1; i >= 0; i--) {
        next_occ[i] = next_pos[c[i]];
        next_pos[c[i]] = i;
    }

    set<pair<int, int>> machines;
    map<int, int> flavor_to_next;
    int washes = 0;

    for (int i = 0; i < n; i++) {
        int flavor = c[i];
        if (flavor_to_next.count(flavor)) {
            int old_next = flavor_to_next[flavor];
            machines.erase({old_next, flavor});
            machines.insert({next_occ[i], flavor});
            flavor_to_next[flavor] = next_occ[i];
        } else {
            washes++;
            if ((int)machines.size() < k) {
                machines.insert({next_occ[i], flavor});
                flavor_to_next[flavor] = next_occ[i];
            } else {
                auto it = machines.end();
                --it;
                int evict_flavor = it->second;
                machines.erase(it);
                flavor_to_next.erase(evict_flavor);
                machines.insert({next_occ[i], flavor});
                flavor_to_next[flavor] = next_occ[i];
            }
        }
    }

    cout << washes << endl;
    return 0;
}
```

## 解题思路

### 问题分析

有 k 台冰淇淋机器，n 个顾客依次请求口味 c[i]（1≤c[i]≤m）。每台机器只能装一种口味，若当前机器中没有请求的口味则需要清洗一台机器并装入新口味。目标是最小化清洗次数。

### 核心思路

经典缓存替换问题，使用 Belady 算法（贪心策略）：当需要淘汰时，选择下次使用最远（或不再使用）的口味。用 set 维护当前机器中的口味及其下次使用位置，用 map 快速查找和更新。

### 算法流程

1. 预处理每个位置的下一个相同口味的位置 next_occ[i]（从后往前遍历）
2. 维护 set<pair<int,int>> machines，按下次使用位置排序
3. 遍历每个请求：
   - 若口味已在机器中：更新其下次使用位置
   - 若不在且机器未满：直接装入，清洗次数+1
   - 若不在且机器已满：淘汰 set 中下次使用最远的口味，装入新口味，清洗次数+1
4. 输出清洗次数

### 复杂度分析

- 时间复杂度：O(n log k)，预处理 O(n)，遍历中 set 操作 O(log k)
- 空间复杂度：O(n + m)
