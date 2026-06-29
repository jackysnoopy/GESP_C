# Supermarket

## 题目描述

有 n 件商品，每件商品有一个利润 profit 和一个截止日期 deadline（在第 deadline 天及之前必须卖出）。每天最多卖一件商品。求最大总利润。

## 输入格式

- 多组测试数据，每组第一行一个整数 n
- 接下来 n 行，每行两个整数 profit 和 deadline
- 输入以 EOF 结束

## 输出格式

每组数据输出一个整数，表示最大总利润

## 样例

```
输入：
4
50 2
10 1
20 2
30 1

输出：
80
```

## 提示

- 使用贪心算法，按利润从大到小排序
- 使用并查集快速找到某个截止日期之前的最新可用日期

## 解题思路

### 问题分析

这是一个经典的调度问题。每件商品需要在截止日期之前安排一天出售，目标是最大化总利润。

### 核心思路

贪心策略：按利润从高到低依次考虑每件商品，尽量将其安排在截止日期或之前最晚的可用日期。使用并查集维护每个日期的可用性——如果第 d 天已占用，则并查集指向 d-1 天。

### 算法流程

1. 将所有商品按利润从大到小排序
2. 初始化并查集，每个日期指向自身
3. 对于每件商品 (profit, deadline)：
   - 找到 deadline 之前最新的可用日期 day = find(min(deadline, max_d))
   - 若 day > 0，则将该商品安排在第 day 天，累加利润
   - 将第 day 天标记为已占用：parent[day] = find(day - 1)
4. 输出总利润

### 复杂度分析

- 时间复杂度：O(n × α(n))，其中 α 是反阿克曼函数
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item { int profit, deadline; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<Item> items(n);
        int max_d = 0;
        for (int i = 0; i < n; i++) {
            cin >> items[i].profit >> items[i].deadline;
            max_d = max(max_d, items[i].deadline);
        }
        
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.profit > b.profit;
        });
        
        vector<int> parent(max_d + 2);
        for (int i = 0; i <= max_d + 1; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        
        int ans = 0;
        for (const auto& item : items) {
            int day = find(min(item.deadline, max_d));
            if (day > 0) {
                ans += item.profit;
                parent[day] = find(day - 1);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```
