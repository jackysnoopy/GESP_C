# [USACO24DEC] Job Completion G

## 题目描述
奶牛 Bessie 有 $N$ 个工作。第 $i$ 个工作必须在时刻 $s_i$ 或之前开始，花费 $t_i$ 时间完成。求可以完成的最大工作数量。时间从时刻 $0$ 开始，一旦开始一个工作必须完成才能开始下一个。

## 输入格式
第一行 $T$（测试用例数）。每个测试用例：第一行 $N$，接下来 $N$ 行每行 $s_i, t_i$。

## 输出格式
每个测试用例一行，最大可完成工作数。

## 样例
输入：
```
3
2
1 4
1 2
2
2 3
1 2
3
1 4
2 3
1 2
```
输出：
```
1
2
2
```

## 提示
$1 \le T \le 10$，所有测试用例 $N$ 之和 $\le 3 \times 10^5$，$0 \le s_i \le 10^{18}$，$1 \le t_i \le 10^{18}$。

## 解题思路

### 问题分析
经典的带截止时间调度问题。需要贪心地选择工作，使得在不超过截止时间的前提下完成尽可能多的工作。

### 核心思路
按截止时间 $s_i$ 升序排序。维护当前时间和一个大根堆（存已完成工作的耗时）。依次尝试加入每个工作：
1. 将当前工作加入，更新时间
2. 若超时，移除堆中耗时最大的工作

这样保证每次超时时丢弃代价最大的工作，从而保留最多的工作。

### 算法流程
1. 按 $s_i$ 排序
2. 依次处理每个工作，加入堆并累加时间
3. 若超时则弹出堆顶
4. 答案为堆的大小

### 复杂度分析
- 时间：$O(N \log N)$
- 空间：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> jobs(n);
        for (int i = 0; i < n; i++) {
            cin >> jobs[i].first >> jobs[i].second;
        }
        sort(jobs.begin(), jobs.end());
        priority_queue<long long> pq;
        long long curTime = 0;
        for (int i = 0; i < n; i++) {
            curTime += jobs[i].second;
            pq.push(jobs[i].second);
            if (curTime > jobs[i].first) {
                curTime -= pq.top();
                pq.pop();
            }
        }
        cout << pq.size() << "\n";
    }
    return 0;
}
```
