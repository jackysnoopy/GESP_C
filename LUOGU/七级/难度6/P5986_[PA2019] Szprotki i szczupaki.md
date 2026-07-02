# P5986 [PA2019] Szprotki i szczupaki

## 题目信息

- **题目来源**: PA2019
- **难度**: 7
- **标签**: 贪心、数据结构、multiset

## 题意简述

有 n 条小鱼，重量分别为 w_i。支持三种操作：
1. `1 s k`：一条重量为 s 的鲨鱼询问：如果每次严格大于自身时吃掉最轻的鱼并增加自身重量，最少吃几条鱼才能使自身重量 >= k？如果不可能输出 -1。
2. `2 w`：加入一条重量为 w 的鱼。
3. `3 w`：删除一条重量为 w 的鱼。

## 解题思路

### 贪心策略

对于询问 `1 s k`：
1. 如果 `s >= k`，答案为 0，无需吃鱼。
2. 否则需要吃鱼。每次吃鱼时，我们**严格**需要吃一条**大于自身当前重量**的鱼。
3. **贪心策略**：每次吃严格大于自身的**最轻**的鱼。

### 为什么贪心正确？

- 如果当前重量为 cur，我们需要找一条重量 w > cur 的鱼。
- 吃完这条鱼后，新重量变为 cur + w。
- 我们总是选择最小的 w > cur，这样可以最小化消耗，同时让 cur 尽快增长。
- 由于每次 cur 都会增加，所需的鱼重量会越来越大，所以贪心是正确的。

### 数据结构选择

使用 `multiset` 来维护鱼的重量：
- `insert`：添加鱼 O(log n)
- `find + erase`：删除鱼 O(log n)
- `upper_bound(cur)`：找到严格大于 cur 的最轻鱼 O(log n)

### 算法流程

对于每个询问 `1 s k`：
1. 初始化 `cur = s, cnt = 0`
2. 如果 `cur >= k`，输出 0
3. 否则：
   - 用 `upper_bound(cur)` 找到严格大于 cur 的最轻鱼
   - 如果找不到，输出 -1
   - 否则 `cur += w, cnt++`
   - 重复直到 `cur >= k` 或找不到鱼
4. 输出 cnt

## 复杂度分析

- **时间复杂度**：每次操作 O(log n)，查询操作需要复制multiset O(n)，总复杂度 O(n * q)
- **空间复杂度**：O(n)

## 代码实现

```cpp
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    multiset<long long> fish;
    for (int i = 0; i < n; i++) {
        long long w;
        cin >> w;
        fish.insert(w);
    }
    
    int q;
    cin >> q;
    
    while (q--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            long long s, k;
            cin >> s >> k;
            
            if (s >= k) {
                cout << 0 << "\n";
                continue;
            }
            
            int cnt = 0;
            long long cur = s;
            bool ok = false;
            multiset<long long> temp = fish;
            
            while (cur < k) {
                auto it = temp.upper_bound(cur);
                if (it == temp.end()) {
                    break;
                }
                cur += *it;
                temp.erase(it);
                cnt++;
                if (cur >= k) {
                    ok = true;
                    break;
                }
            }
            
            if (ok) {
                cout << cnt << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else if (op == 2) {
            long long w;
            cin >> w;
            fish.insert(w);
        } else {
            long long w;
            cin >> w;
            auto it = fish.find(w);
            if (it != fish.end()) {
                fish.erase(it);
            }
        }
    }
    
    return 0;
}
```

## 易错点

1. **删除操作**：使用 `find` 后 `erase(it)` 只删除一个元素，不是删除所有相同值的元素。
2. **数据范围**：鱼的重量可达 10^12，s 和 k 可达 10^18，需要使用 `long long`。
3. **upper_bound vs lower_bound**：题目要求严格大于自身，所以用 `upper_bound`。

## 总结

本题是一道贪心+数据结构的经典题目，关键在于识别出贪心策略（每次吃最轻的可吃的鱼），并用 multiset 实现高效查询。
