# [USACO22OPEN] Apple Catching G

## 题目描述
天上下苹果了！在某些时刻，一定数量的苹果会落到数轴上。在某些时刻，Farmer John 的一些奶牛将到达数轴并开始接苹果。

如果一个苹果在没有奶牛接住的情况下落到数轴上，它就会永远消失。如果一头奶牛和一个苹果同时到达，奶牛就会接住苹果。每头奶牛每秒可以移动一单位距离。一旦一头奶牛接住了一个苹果，她就会离开数轴。

如果 FJ 的奶牛以最优方式合作，她们总共能接住多少个苹果？

## 输入格式
输入的第一行包含 $N$（$1\le N\le 2\cdot 10^5$），为苹果落到数轴上的次数或 FJ 的奶牛出现的次数。

以下 $N$ 行每行包含四个整数 $q_i$，$t_i$，$x_i$ 和 $n_i$（$q_i\in \{1,2\}, 0\le t_i\le 10^9, 0\le x_i\le 10^9, 1\le n_i\le 10^3$）。

- 如果 $q_i=1$，意味着 FJ 的 $n_i$ 头奶牛在 $t_i$ 时刻来到数轴上的 $x_i$ 位置。
- 如果 $q_i=2$，意味着 $n_i$ 个苹果在 $t_i$ 时刻落到了数轴上的 $x_i$ 位置。

输入保证所有有序对 $(t_i,x_i)$ 各不相同。

## 输出格式
输出 FJ 的奶牛总计能接住的苹果的最大数量。

## 样例
### 样例1
输入:
```
5
2 5 10 100
2 6 0 3
2 8 10 7
1 2 4 5
1 4 7 6
```
输出:
```
10
```

### 样例2
输入:
```
5
2 5 10 100
2 6 0 3
2 8 11 7
1 2 4 5
1 4 7 6
```
输出:
```
9
```

## 提示
- 时间限制：2000ms
- 内存限制：262144KB

## 解题思路

### 问题分析
这是一个贪心匹配问题。奶牛需要在有限时间内到达苹果位置，每头奶牛只能接一个苹果。

### 核心思路
1. 按时间排序所有事件
2. 奶牛到达时加入优先队列（按位置）
3. 苹果落地时，从优先队列中选择能到达的奶牛进行匹配

### 算法流程
1. 读取所有事件并按时间排序
2. 遍历事件：
   - 奶牛到达：加入优先队列
   - 苹果落地：尝试匹配能到达的奶牛
3. 统计匹配成功的苹果数量

### 复杂度分析
- 时间复杂度：$O(N \log N)$
- 空间复杂度：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Event {
    int type;
    int t, x, n;
    bool operator<(const Event& other) const {
        return t < other.t || (t == other.t && type < other.type);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<Event> events(N);
    for (int i = 0; i < N; i++) {
        cin >> events[i].type >> events[i].t >> events[i].x >> events[i].n;
    }
    
    sort(events.begin(), events.end());
    
    long long ans = 0;
    priority_queue<int> cows;
    
    for (const auto& e : events) {
        if (e.type == 1) {
            for (int i = 0; i < e.n; i++) {
                cows.push(e.x);
            }
        } else {
            vector<int> remaining;
            int caught = 0;
            
            while (!cows.empty() && caught < e.n) {
                int cow_pos = cows.top();
                cows.pop();
                
                if (abs(cow_pos - e.x) <= e.t) {
                    caught++;
                } else {
                    remaining.push_back(cow_pos);
                }
            }
            
            ans += caught;
            
            for (int pos : remaining) {
                cows.push(pos);
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
```