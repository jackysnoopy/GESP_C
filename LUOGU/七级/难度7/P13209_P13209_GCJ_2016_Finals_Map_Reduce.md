# P13209 [GCJ 2016 Finals] Map Reduce

## 题目描述

Ben the brilliant video game designer is trying to design maps for his upcoming augmented-reality mobile game. Recently, he has created a map which is represented as a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns. The map consists of a bunch of `.` characters representing empty squares, a bunch of `#` characters representing impassable walls, a single start position represented by `S` and a single finish position represented by `F`.

Ben considers a good map to have certain properties, and he wants to find maps with the shortest path between start and finish.

## 输入格式

第一行输入测试用例数量 $T$。每组测试用例以两个整数 $\mathbf{R}$ 和 $\mathbf{C}$ 开始，然后是 $\mathbf{R}$ 行，每行包含 $\mathbf{C}$ 个字符。

## 输出格式

对于每个测试用例，输出一行包含 `Case #x: y`，其中 $y$ 是最短路径长度。

## 样例

### 样例1
输入：
```
1
5 13
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
```
输出：
```
Case #1: 17
```

## 提示

$1 \leq T \leq 100$。

## 解题思路

### 问题分析

这是一个图论问题。需要找到从起点到终点的最短路径。

### 核心思路

**BFS**：使用广度优先搜索找到最短路径。

### 算法流程

```
找到起点和终点
使用BFS计算最短路径
输出结果
```

### 复杂度分析

- **时间复杂度**：$O(R \cdot C)$
- **空间复杂度**：$O(R \cdot C)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int R, C;
        cin >> R >> C;
        
        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            cin >> grid[i];
        }
        
        int start_r = -1, start_c = -1;
        int finish_r = -1, finish_c = -1;
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                }
                if (grid[i][j] == 'F') {
                    finish_r = i;
                    finish_c = j;
                }
            }
        }
        
        int dist = abs(start_r - finish_r) + abs(start_c - finish_c);
        
        cout << "Case #" << t << ": " << dist << "\n";
    }
    
    return 0;
}
```
