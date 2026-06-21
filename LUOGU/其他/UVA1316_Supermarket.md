# Supermarket

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 输入格式


## 输出格式


## 样例
### 样例 1
```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10
```
```
80 
185
```

## 解题思路
### 问题分析
n 个商品各有利润和截止日期，每天只能卖一个，求最大利润。

### 核心思路
贪心 + 并查集。按利润降序排序，对每个商品找截止日期前最晚的空闲时间。

### 算法流程
1. 读入 n 和 (利润, 截止)
2. 按利润降序排序
3. 用并查集维护已占用时间，找前驱空闲时间
4. 累加利润

### 复杂度分析
- 时间复杂度：O(n log n)
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
