# P1607 [USACO09FEB] Fair Shuttle G

## 思路

核心算法：贪心+优先队列

## 解题思路

### 问题分析
 shuttle 沿直线行驶，容量为 c。k 组乘客在不同站点上下车，每组有起始站 s、终点站 e、人数 m。求最多能运送多少乘客。

### 核心思路
贪心 + 优先队列：按终点站排序，在每个站点先让到达的乘客下车，再尽量让新乘客上车。

### 算法流程
1. 将所有乘客组按终点站 e 排序
2. 遍历每组乘客：
   - 用优先队列（按终点站）移除已到达终点的乘客，释放容量
   - 尽量让当前组乘客上车（不超过剩余容量）
3. 累加总运送人数

### 复杂度分析
- 时间复杂度：O(k log k)
- 空间复杂度：O(k)

```cpp

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Group {
    int s, e, m;
};

bool compareEnd(const Group& a, const Group& b) {
    return a.e < b.e;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, n, c;
    cin >> k >> n >> c;
    
    vector<Group> groups(k);
    for (int i = 0; i < k; i++) {
        cin >> groups[i].s >> groups[i].e >> groups[i].m;
    }
    
    // Sort by end position
    sort(groups.begin(), groups.end(), compareEnd);
    
    // Use a priority queue to track active cows at each stop
    // At each stop, remove cows that have reached their destination
    // Then add new cows if capacity allows
    
    long long total = 0;
    priority_queue<pair<int, int>> active; // (end position, count)
    int current_load = 0;
    
    for (int i = 0; i < k; i++) {
        // Remove cows that have reached their destination
        while (!active.empty() && active.top().first <= groups[i].s) {
            current_load -= active.top().second;
            active.pop();
        }
        
        // Add cows from current group
        int can_add = min(groups[i].m, c - current_load);
        if (can_add > 0) {
            total += can_add;
            current_load += can_add;
            active.push({groups[i].e, can_add});
        }
    }
    
    cout << total << "\n";
    return 0;
}
```
