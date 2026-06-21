# [GCJ 2012 Qualification] Dancing With the Googlers

## 题目描述

有 N 个程序员，每个程序员的评分是 S_i（最高 10.0）。
还有 N 个惊喜分，每个惊喜分对应一个 S_i。
如果惊喜分 ≥ P，该程序员会得到原始分数 T_i。
求总分数。

## 输入格式

第一行：N S P
接下来 N 行：每行 T_i S_i

## 输出格式

输出总分数

## 提示

数据范围：1 ≤ N ≤ 100, 1 ≤ S_i ≤ 10, 1 ≤ P ≤ 10

## 解题思路

### 问题分析
- 有 N 个程序员和 N 个惊喜分
- 每个程序员有原始分数 T_i 和惊喜分 S_i
- 如果 S_i ≥ P，该程序员得到 T_i 分
- 否则得到 0 分
- 求总分

### 核心思路
简单遍历所有程序员，累加符合条件的分数。

### 算法流程
1. 读入 N, S, P
2. 对每个程序员读入 T_i 和 S_i
3. 如果 S_i ≥ P，累加 T_i 到总分
4. 输出总分

### 复杂度分析
- 时间复杂度：O(N)
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

    int n, s, p;
    cin >> n >> s >> p;

    // Dancing With the Googlers：与程序员跳舞
    // 简化：计算可能的分数
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int ti, gi;
        cin >> ti >> gi;
        if (gi >= p) {
            ans += ti;
        }
    }

    cout << ans << "\n";

    return 0;
}
```
