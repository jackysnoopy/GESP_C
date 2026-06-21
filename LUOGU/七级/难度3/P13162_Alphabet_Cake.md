# [GCJ 2017 #1A] Alphabet Cake

## 题目描述

你有一个 R 行 C 列的网格，每个格子可以是空的或有字母 A-Y（不含 Z）。
你需要用字母 A-Y 填满这个网格，使得相邻格子不同（水平或垂直相邻）。

## 输入格式

第一行：R C

## 输出格式

如果可能，输出填满的网格；否则输出 "IMPOSSIBLE"

## 提示

数据范围：1 ≤ R, C ≤ 25

## 解题思路

### 问题分析
- 给定一个网格，某些格子有字母，某些为空
- 需要用字母 A-Y 填满
- 要求相邻格子不同（水平或垂直相邻）

### 核心思路
**搜索策略**：
1. 从左上角开始，逐行逐列填充
2. 对于每个格子，检查上方和左方已填的字母
3. 从可用字母中选择一个不冲突的字母
4. 如果无法选择，回溯或输出 "IMPOSSIBLE"

### 算法流程
1. 读入 R, C
2. 从左上角开始遍历网格
3. 对于每个格子，检查限制并选择字母
4. 如果完成，输出网格；否则输出 "IMPOSSIBLE"

### 复杂度分析
- 时间复杂度：O(R × C × 25)，每个格子最多尝试25个字母
- 空间复杂度：O(R × C)

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

    // Alphabet Cake：字母蛋糕
    int ans = 0;
    for (int i = 0; i < n;; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 0) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
```
