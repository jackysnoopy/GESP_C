# City Game

## 题目描述

给定一个 n×m 的网格，包含字符 'F'（地板）和 'M'（墙壁）。求网格中最大的全 'F' 子矩形面积（每个单元格面积为 3）。

## 输入格式

- 第一行一个整数 T，表示测试数据组数
- 每组数据第一行两个整数 n 和 m
- 接下来 n 行，每行 m 个字符

## 输出格式

每组数据输出一个整数，表示最大全 'F' 子矩形的面积（单元格数 × 3）

## 样例

```
输入：
1
6 5
MFFMFF
MFFMFF
MFFMFF
MFFMFF
MFFMFF
MFFMFF

输出：
45
```

## 提示

- 使用直方图方法逐行处理
- 对于每行，计算以该行为底边的最大矩形

## 解题思路

### 问题分析

在 01 矩阵中找最大全 1 子矩形，可以转化为每行的直方图最大矩形问题。

### 核心思路

维护一个高度数组 h[j]，表示以当前行为底边、第 j 列连续 'F' 的个数。对于每行，使用单调栈计算以该行为底边的最大矩形面积，取所有行的最大值。

### 算法流程

1. 初始化高度数组 h[1..m] = 0
2. 对于每一行：
   - 若当前位置为 'F'，h[j]++；否则 h[j] = 0
   - 使用单调栈计算当前直方图的最大矩形面积
3. 输出最大面积 × 3

### 复杂度分析

- 时间复杂度：O(n × m)
- 空间复杂度：O(m)

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
    
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<int> h(m + 2, 0);
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                char c; cin >> c;
                if (c == 'F') h[j]++;
                else h[j] = 0;
            }
            
            stack<int> st;
            st.push(0);
            for (int j = 1; j <= m + 1; j++) {
                while (h[j] < h[st.top()]) {
                    int height = h[st.top()]; st.pop();
                    ans = max(ans, height * (j - st.top() - 1));
                }
                st.push(j);
            }
        }
        
        cout << ans * 3 << "\n";
    }
    return 0;
}
```
