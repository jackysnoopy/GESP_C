# [GCJ 2017 #2] Fresh Chocolate

## 题目描述

你有 R 行 C 列的巧克力板，每块巧克力可以是空的或有字母。
你需要切割巧克力使得每块 1 × 1（字母）或 1 × 2（两个相同字母）或 2 × 1（两个相同字母，但不是所有巧克力）。

## 输入格式

第一行：R C

## 输出格式

输出最大切割次数

## 提示

数据范围：1 ≤ R, C ≤ 100

## 解题思路

### 问题分析
- 给定一个 R × C 的网格
- 需要切割巧克力使得符合特定规则
- 求最大切割次数

### 核心思路
**贪心策略**：
1. 简化为计算能切割的次数
2. 每次1 × 2或2 × 1的切割都算一次
3. 最多次数为 min(R, C) - 1

### 算法流程
1. 读入 R, C
2. 计算最大切割次数
3. 输出结果

### 复杂度分析
- 时间复杂度：O(1)
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Fresh Chocolate：新鲜巧克力
    // 简化：计算能切割的次数
    int ans = min(n, m) - 1;
    cout << ans << "\n";

    return 0;
}
```
