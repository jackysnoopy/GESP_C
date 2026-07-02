# [JOISC 2021] イベント巡り 2 (Event Hopping 2) (Day4)

## 题目描述

IOI Park 将有 n 场活动。JOI 君决定参加其中的 k 个活动，但不能在中间加入或离开每个活动。JOI 君希望参加编号较小的活动，需要判断是否可以参加 k 个活动，如果可以，输出所有 k 个活动的编号（最小字典序）。

## 输入格式

第一行，两个正整数 n,k。
第 2~n+1 行，每行 2 个正整数，Li, Ri。

## 输出格式

如果 JOI 君可以参加 k 个活动，输出 k 行，每行一个活动编号（最小字典序）。
如果无法参加 k 个活动，输出 -1。

## 样例

### 样例 1
输入：
```
5 4
1 3
2 5
8 9
6 8
10 15
```
输出：
```
1
3
4
5
```

### 样例 2
输入：
```
4 3
1 4
3 5
4 9
7 10
```
输出：
```
-1
```

## 提示

对于 100% 的数据：1≤n≤10^5，1≤k≤n，1≤Li<Ri≤10^9。

## 解题思路

### 问题分析
需要选择 k 个不重叠的活动，且编号字典序最小。

### 核心思路
使用贪心算法，每次选择字典序最小的可行活动。

### 算法流程
1. 按开始时间排序活动
2. 使用 multiset 维护可用的结束时间
3. 每次选择字典序最小的合法活动

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Event {
    int l, r, id;
    bool operator<(const Event& other) const {
        return l < other.l;
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    vector<Event> events(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &events[i].l, &events[i].r);
        events[i].id = i + 1;
    }
    
    sort(events.begin(), events.end());
    
    vector<int> result;
    multiset<int> available_end;
    int event_idx = 0;
    
    for (int i = 0; i < k; i++) {
        int earliest_end = available_end.empty() ? events[event_idx].l : *available_end.begin();
        
        while (event_idx < n && events[event_idx].l <= earliest_end) {
            available_end.insert(events[event_idx].r);
            event_idx++;
        }
        
        if (available_end.empty()) {
            printf("-1\n");
            return 0;
        }
        
        int best_idx = -1;
        for (int j = 0; j < n; j++) {
            if (events[j].id > 0 && events[j].l >= (result.empty() ? 0 : events[result.back()-1].r)) {
                bool valid = true;
                for (int r : result) {
                    if (events[r-1].r > events[j].l) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    best_idx = j;
                    break;
                }
            }
        }
        
        if (best_idx == -1) {
            printf("-1\n");
            return 0;
        }
        
        result.push_back(best_idx + 1);
    }
    
    for (int id : result) {
        printf("%d\n", id);
    }
    
    return 0;
}
```