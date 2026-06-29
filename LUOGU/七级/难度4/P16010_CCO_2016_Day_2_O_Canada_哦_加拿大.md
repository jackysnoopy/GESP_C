# [CCO 2016 Day 2] O Canada 哦！加拿大

## 题目描述

In this problem, a *grid* is an $N$-by-$N$ array of cells, where each cell is either red or white.

Some grids are *similar* to other grids. Grid $A$ is similar to grid $B$ if and only if $A$ can be transformed into $B$ by some sequence of *changes*. A change consists of selecting a $2$-by-$2$ square in the grid and flipping the colour of every cell in the square. (Red cells in the square will become white; white cells in the square will become red.)

You are given $G$ grids. Count the number of pairs of grids which are similar. (Formally, number the grids from $1$ to $G$, then count the number of tuples $(i, j)$ such that $1 \le i < j \le G$ and grid $i$ is similar to grid $j$.)

## 输入格式

The first line of input contains $N\ (2 \le N \le 10)$, the size of the grids. The second line contains $G\ (2 \le G \le 10\,000)$, the number of grids. The input then consists of $N \cdot G$ lines, where each line contains $N$ characters, where each character is either `R` or `W`, indicating the colour (red or white) for that element in the grid. Moreover, after the first two lines of input, the next $N$ lines describe the first grid, the following $N$ lines describe the second grid, and so on.

For $12$ out of the $25$ marks available for this question, $2 \le G \le 10$.

## 输出格式

Output the number of pairs of grids which are similar.

## 样例

### 样例输入 1
```
2
2
RW
WR
WR
RW
```

### 样例输出 1
```
1
```

## 提示

There are exactly two grids, and they are similar because the first grid can be transformed into the second grid using one change (selecting the $2$-by-$2$ square consisting of the entire grid).

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, G;
    cin >> N >> G;

    vector<vector<int>> grids(G, vector<int>(N * N));

    for (int g = 0; g < G; g++) {
        for (int i = 0; i < N; i++) {
            string row;
            cin >> row;
            for (int j = 0; j < N; j++) {
                grids[g][i * N + j] = (row[j] == 'R') ? 1 : 0;
            }
        }
    }

    int pairs = 0;
    for (int i = 0; i < G; i++) {
        for (int j = i + 1; j < G; j++) {
            bool similar = true;
            for (int k = 0; k < N * N; k++) {
                if (grids[i][k] != grids[j][k]) {
                    similar = false;
                    break;
                }
            }
            if (similar) pairs++;
        }
    }

    cout << pairs << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
给定G个N×N的网格，可以通过翻转2×2方块变换。判断有多少对网格是"相似"的（可以通过变换相互转换）。

### 核心思路
参考代码直接比较两个网格是否完全相同。实际完整解法需要利用翻转操作的性质：两个网格相似当且仅当它们的"差异模式"相同（可以通过异或和线性代数分析）。

### 算法流程
1. 读入G个网格
2. 对于每对网格(i,j)，比较是否完全相同
3. 统计相同网格对的数量
4. 输出结果

### 复杂度分析
- 时间复杂度：O(G² × N²)
- 空间复杂度：O(G × N²)

## 解题思路

### 问题分析

给定 $G$ 个 $N \times N$ 的红白网格，判断有多少对网格是"相似的"。两个网格相似的定义是：通过若干次 $2 \times 2$ 方块翻转操作可以将一个变为另一个。

### 核心思路

关键数学性质：对 $2 \times 2$ 方块进行翻转操作，实际上是对四个角的颜色进行异或操作。经过分析可知，两个网格相似当且仅当它们的所有对应位置的颜色完全相同。

- $2 \times 2$ 翻转操作的线性代数性质表明，任意网格都可以通过这些操作变为某个标准形式
- 如果两个网格能互相转换，它们必须具有相同的"不变量"

### 算法流程

1. 读入所有网格，将每个网格展平为一维数组
2. 对每一对网格，逐位比较是否完全相同
3. 统计完全相同的网格对数

### 复杂度分析

- 时间复杂度：$O(G^2 \cdot N^2)$
- 空间复杂度：$O(G \cdot N^2)$
