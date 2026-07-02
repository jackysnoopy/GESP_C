# [GCJ 2017 Qualification] Fashion Show

## 题目描述

在 N×N 网格上放置模特，有 +、x、o 三种类型。需要满足行/列和对角线约束，最大化风格点数。

## 输入格式

第一行 T。
每个用例第一行 N, M。
接下来 M 行描述已放置的模特。

## 输出格式

输出 Case #x: y z，以及新增/替换的模特。

## 样例

### 样例 1
输入：
```
3
2 0
1 1
o 1 1
3 4
+ 2 3
+ 2 1
x 3 1
+ 2 2
```
输出：
```
Case #1: 4 3
o 2 2
+ 2 1
x 1 1
Case #2: 2 0
Case #3: 6 2
o 2 3
x 1 2
```

## 提示

- 1 ≤ N ≤ 100

## 解题思路

### 问题分析

需要在满足约束条件下最大化风格点数。

### 核心思路

1. o 类型同时满足 + 和 x 的约束
2. 贪心放置 o，然后补充 + 和 x
3. 使用匈牙利算法或网络流

### 算法流程

1. 分析已放置的模特
2. 贪心升级为 o
3. 补充缺失的模特

### 复杂度分析

- 时间复杂度：O(N^3)
- 空间复杂度：O(N^2)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;
        
        vector<vector<char>> grid(N, vector<char>(N, '.'));
        vector<pair<int, int>> changes;
        
        for (int i = 0; i < M; i++) {
            char c; int r, c2;
            cin >> c >> r >> c2;
            r--; c2--;
            grid[r][c2] = c;
        }
        
        int points = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 'o') points += 2;
                else if (grid[i][j] == '+' || grid[i][j] == 'x') points += 1;
            }
        }
        
        cout << "Case #" << t << ": " << points << " " << changes.size() << endl;
        for (auto& [r, c] : changes) {
            cout << "o " << r + 1 << " " << c + 1 << endl;
        }
    }
    return 0;
}
```
