# [USACO06FEB] Stall Reservations S

## 题目描述
Oh those picky $N$ ($1 \leq N \leq 50,000$) cows! They are so picky that each one will only be milked over some precise time interval $[A,B]$ ($1 \leq A \leq B \leq 1,000,000$), which includes both times $A$ and $B$. Obviously, FJ must create a reservation system to determine which stall each cow can be assigned for her milking time. Of course, no cow will share such a private moment with other cows.

Help FJ by determining: The minimum number of stalls required in the barn so that each cow can have her private milking period. An assignment of cows to these stalls over time. Many answers are correct for each test dataset; a program will grade your answer.

## 输入格式
Line $1$: A single integer, $N$.

Lines $2 \sim N+1$: Line $i+1$ describes cow $i$'s milking interval with two space-separated integers.

## 输出格式
Line $1$: The minimum number of stalls the barn must have.

Lines $2 \sim N+1$: Line $i+1$ describes the stall to which cow i will be assigned for her milking period.

## 样例
### 样例 1
```
5
1 10
2 4
3 6
5 8
4 7
```
```
4
1
2
3
2
4
```

## 提示
**Explanation of the sample:**

Here's a graphical schedule for this output:

```plain
Time     1  2  3  4  5  6  7  8  9 10


Stall 1 c1>>>>>>>>>>>>>>>>>>>>>>>>>>>


Stall 2 .. c2>>>>>> c4>>>>>>>>> .. ..


Stall 3 .. .. c3>>>>>>>>> .. .. .. ..


Stall 4 .. .. .. c5>>>>>>>>> .. .. ..
```

Other outputs using the same number of stalls are possible.

## 解题思路

### 问题分析
N 头奶牛有挤奶时间区间 [start, end]，需要安排到畜栏中，每头牛的区间不能重叠。求最少畜栏数及每头牛分配的畜栏编号。

### 核心思路
区间分组贪心。按开始时间排序，用小根堆维护当前畜栏的最早结束时间。

### 算法流程
1. 读入 N 和每头牛的区间
2. 按开始时间升序排序
3. 用优先队列维护（结束时间, 畜栏编号）
4. 每头牛看堆顶是否可复用，否则新建畜栏
5. 输出结果

### 复杂度分析
- 时间复杂度：O(N log N)
- 空间复杂度：O(N)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Cow {
    int start, end, id;
};

struct Stall {
    int end, idx;
    bool operator>(const Stall& other) const {
        return end > other.end;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<Cow> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].start >> cows[i].end;
        cows[i].id = i;
    }
    
    sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
        return a.start < b.start;
    });
    
    priority_queue<Stall, vector<Stall>, greater<Stall>> pq;
    vector<int> ans(N);
    int cnt = 0;
    
    for (const auto& cow : cows) {
        if (!pq.empty() && pq.top().end < cow.start) {
            ans[cow.id] = pq.top().idx;
            pq.pop();
            pq.push({cow.end, ans[cow.id]});
        } else {
            ans[cow.id] = ++cnt;
            pq.push({cow.end, cnt});
        }
    }
    
    cout << cnt << "\n";
    for (int x : ans) cout << x << "\n";
    
    return 0;
}
```
