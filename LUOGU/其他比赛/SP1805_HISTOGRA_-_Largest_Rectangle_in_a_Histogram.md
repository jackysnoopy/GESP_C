# HISTOGRA - Largest Rectangle in a Histogram

## 题目描述

给定一个由 n 个非负整数组成的直方图，每个整数表示对应柱子的高度。求直方图中能够勾画出的最大矩形面积。

## 输入格式

- 多组测试数据，每组第一行一个整数 n（0 表示结束）
- 接下来 n 个整数，表示每个柱子的高度

## 输出格式

每组数据输出一个整数，表示最大矩形面积

## 样例

```
输入：
7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0

输出：
8
4000
```

## 提示

- 使用单调栈可以在 O(n) 时间内解决
- 注意处理柱子高度为 0 的情况

## 解题思路

### 问题分析

对于每个柱子，需要找到以其高度为高的最大矩形，即找到左右两边第一个比它矮的柱子位置。

### 核心思路

使用单调递增栈。维护一个栈，栈中元素严格递增。当遇到比栈顶矮的柱子时，弹出栈顶并计算以该柱子高度为高的矩形面积。

### 算法流程

1. 在直方图两端各添加一个高度为 0 的哨兵柱子
2. 初始化单调栈，压入左哨兵的下标
3. 遍历每个柱子（包括右哨兵）：
   - 当前柱子高度 < 栈顶柱子高度时，弹出栈顶：
     - 高度 = 弹出柱子的高度
     - 宽度 = 当前下标 - 新栈顶下标 - 1
     - 更新最大面积
   - 将当前下标压入栈
4. 输出最大面积

### 复杂度分析

- 时间复杂度：O(n)，每个元素最多入栈出栈各一次
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        vector<long long> h(n + 2, 0);
        for (int i = 1; i <= n; i++) cin >> h[i];
        
        stack<int> st;
        st.push(0);
        long long ans = 0;
        for (int i = 1; i <= n + 1; i++) {
            while (h[i] < h[st.top()]) {
                long long height = h[st.top()]; st.pop();
                long long width = i - st.top() - 1;
                ans = max(ans, height * width);
            }
            st.push(i);
        }
        cout << ans << "\n";
    }
    return 0;
}
```
