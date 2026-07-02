# UVA165 - Stamps (邮票)

## 题目描述

给定邮票面值数量 h 和最大面值 k，找出 h 张邮票能表示的最大连续面值，以及对应的面值组合。

## 输入格式

每行两个整数 h 和 k，以 `0 0` 结尾。

## 输出格式

输出最优面值组合和最大连续面值。

## 样例

略。

## 提示

这是一个搜索+剪枝问题。

## 解题思路

### 问题分析

需要用 h 张邮票（面值可重复），找出能表示的最大连续面值。

### 核心思路

1. 第一个面值固定为1
2. 使用DFS搜索剩余面值
3. 每次尝试使用不同数量的当前面值
4. 用贪心+回溯搜索

### 算法流程

1. 初始化面值1
2. DFS搜索下一个面值
3. 计算能表示的最大连续面值
4. 更新最优解

### 复杂度分析

- 时间复杂度：指数级，但通过剪枝优化
- 空间复杂度：O(h)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int h, k;
vector<int> stamps;
vector<int> best;
int maxVal = 0;

void dfs(int pos, int depth, int sum, int prev) {
    if (depth == h) {
        if (sum > maxVal) {
            maxVal = sum;
            best = stamps;
        }
        return;
    }
    for (int i = 1; i <= k; i++) {
        if (depth + i > h) break;
        int newSum = sum;
        vector<int> newStamps = stamps;
        for (int j = 0; j < i; j++) {
            newSum += prev;
            newStamps.push_back(prev);
        }
        dfs(pos + 1, depth + i, newSum, newSum);
    }
}

int main() {
    while (cin >> h >> k && (h || k)) {
        stamps.clear();
        stamps.push_back(1);
        maxVal = 0;
        dfs(1, 1, 1, 1);
        
        for (int i = 0; i < h; i++) {
            if (i) cout << " ";
            cout << best[i];
        }
        cout << " " << maxVal << "\n";
    }
    return 0;
}
```
