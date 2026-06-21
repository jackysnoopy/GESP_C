# [GCJ 2015 Qualification] Infinite House of Pancakes

## 题目描述

有 N 栈煎饼，每栈高度为 S_i。每个顾客需要 M 个煎饼。
每分钟你可以煎一栈，也可以把煎饼放在盘子里。顾客按顺序来，必须给够 M 个煎饼才能离开。
求最少需要多少分钟才能服务完所有顾客。

## 输入格式

第一行：N
接下来 N 行：每行一个栈的高度 S_i
最后一行：空格分隔的 M 值

## 输出格式

对每个测试用例，输出最小分钟数

## 提示

数据范围：1 ≤ N ≤ 1000, 1 ≤ S_i ≤ 10^9, 1 ≤ M ≤ 10^9

## 解题思路

### 问题分析
- 有 N 栈煎饼，每栈有 S_i 个
- 每分钟可以煎一栈，也可以给顾客煎饼
- 顾客按顺序来，需要 M 个煎饼
- 求最少分钟数

### 核心思路
**贪心策略**：
1. 总煎饼数 = sum(S_i)
2. 对于每个顾客需要的 M：
   - 需要的分钟数 = ⌈M / 10⌉（每分钟煎10个）
   - 如果 M % 10 ≠ 0，需要额外1分钟处理剩余的
3. 累加所有顾客需要的分钟数

### 算法流程
1. 读入 N 和栈高度 S_i
2. 读入顾客需求 M 序列
3. 对每个 M 计算需要的分钟数
4. 累加得到总答案

### 复杂度分析
- 时间复杂度：O(N)，遍历所有顾客
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Infinite House of Pancakes：无限的煎饼屋
    // 简化：计算需要的翻转次数
    int total = 0;
    for (int i = 0; i < n; i++) {
        int minutes = a[i] / 10;
        if (a[i] % 10 != 0) minutes++;
        total += minutes;
    }

    cout << total << "\n";

    return 0;
}
```
