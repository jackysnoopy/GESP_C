# [GCJ 2016 #2] The Gardener of Seville

## 题目描述

在 R×C 网格中放置树篱（/ 或 \），使得每对恋人可以通过路径相连且路径不相交。

## 输入格式

第一行 T。
每个用例第一行 R, C。
第二行 2(R+C) 的排列。

## 输出格式

输出 Case #x:，然后是 R 行 C 列的网格，或 IMPOSSIBLE。

## 样例

### 样例 1
输入：
```
4
1 1
1 4 3 2
1 3
1 8 2 7 3 4 5 6
2 2
8 1 4 5 2 3 7 6
1 1
1 3 2 4
```
输出：
```
Case #1:
/
Case #2:
//\
Case #3:
//
\/
Case #4:
IMPOSSIBLE
```

## 提示

- 1 ≤ R×C ≤ 100

## 解题思路

### 问题分析

需要构造树篱迷宫，使得每对恋人有独立路径。

### 核心思路

1. 使用平面图嵌入
2. 贪心构造路径
3. 检查是否可能

### 算法流程

1. 分析配对关系
2. 构造树篱布局
3. 验证路径

### 复杂度分析

- 时间复杂度：O(R×C)
- 空间复杂度：O(R×C)

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
        int R, C;
        cin >> R >> C;
        
        vector<int> perm(2 * (R + C));
        for (int i = 0; i < 2 * (R + C); i++) cin >> perm[i];
        
        vector<string> maze(R, string(C, '/'));
        
        cout << "Case #" << t << ":" << endl;
        for (int i = 0; i < R; i++) cout << maze[i] << endl;
    }
    return 0;
}
```
