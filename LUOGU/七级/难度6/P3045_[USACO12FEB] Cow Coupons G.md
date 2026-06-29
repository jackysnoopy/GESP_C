# P3045 [USACO12FEB] Cow Coupons G

## 思路

核心算法：贪心+优先队列

## 解题思路

### 问题分析

有 n 头牛，每头牛有两个价格：原价 p[i] 和优惠价 c[i]。有 k 张优惠券，每张优惠券只能用一次。给定预算 m，求最多能买多少头牛。

### 核心思路

贪心策略：优先用优惠券购买优惠价最低的牛，然后用原价购买剩余牛中价格最低的。

### 算法流程

1. 读入 n 头牛的原价和优惠价，以及优惠券数量 k 和预算 m
2. 按优惠价排序
3. 用优惠券购买前 min(k, n) 头优惠价最低的牛（在预算范围内）
4. 将剩余牛按原价排序，依次购买（在预算范围内）
5. 输出购买总数

### 复杂度分析

- 时间复杂度：O(n log n)，排序复杂度
- 空间复杂度：O(n)，存储牛的价格信息

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    long long m;
    cin >> n >> k >> m;
    
    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
    }
    
    // Sort by coupon price
    sort(cows.begin(), cows.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    
    // Use priority queue for cows without coupons
    priority_queue<int> pq;
    
    long long total_cost = 0;
    int count = 0;
    
    // First, try to buy cows with coupons
    for (int i = 0; i < min(k, n); i++) {
        if (total_cost + cows[i].second <= m) {
            total_cost += cows[i].second;
            count++;
        } else {
            break;
        }
    }
    
    // Then, try to buy remaining cows with regular prices
    // Sort remaining cows by regular price
    vector<int> remaining;
    for (int i = k; i < n; i++) {
        remaining.push_back(cows[i].first);
    }
    sort(remaining.begin(), remaining.end());
    
    for (int price : remaining) {
        if (total_cost + price <= m) {
            total_cost += price;
            count++;
        } else {
            break;
        }
    }
    
    cout << count << "\n";
    return 0;
}
```
