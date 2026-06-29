# P2949 [USACO09OPEN] Work Scheduling G

## 思路

核心算法：贪心+优先队列

## 解题思路

### 问题分析
有 n 个任务，每个任务有截止时间 deadline 和利润 profit。每个任务耗时 1 个单位时间，求最大总利润。

### 核心思路
贪心策略：按截止时间排序，用小根堆维护已选任务。每遇到一个任务，若当前已选数量 < deadline 则直接选入；否则若该任务利润大于堆顶（最小利润），则替换。

### 算法流程
1. 将任务按截止时间排序
2. 用小根堆维护已选任务的利润
3. 遍历每个任务：
   - 若堆大小 < deadline，直接入堆并累加利润
   - 否则若 profit > 堆顶，弹出堆顶并压入新任务，更新利润
4. 输出总利润

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

```cpp

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> jobs(n);
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].first >> jobs[i].second;
    }
    
    // Sort jobs by deadline
    sort(jobs.begin(), jobs.end());
    
    // Use a min-heap to track selected jobs
    priority_queue<int, vector<int>, greater<int>> pq;
    long long total_profit = 0;
    
    for (int i = 0; i < n; i++) {
        int deadline = jobs[i].first;
        int profit = jobs[i].second;
        
        if (pq.size() < deadline) {
            pq.push(profit);
            total_profit += profit;
        } else if (pq.top() < profit) {
            total_profit -= pq.top();
            pq.pop();
            pq.push(profit);
            total_profit += profit;
        }
    }
    
    cout << total_profit << "\n";
    return 0;
}
```
