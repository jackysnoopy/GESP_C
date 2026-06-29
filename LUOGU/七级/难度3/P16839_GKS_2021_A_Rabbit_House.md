# [GKS 2021 #A] Rabbit House

## 题目描述

Barbara got really good grades in school last year, so her parents decided to gift her with a pet rabbit. She was so excited that she built a house for the rabbit, which can be seen as a $2D$ grid with $R$ rows and $C$ columns.

Rabbits love to jump, so Barbara stacked several boxes on several cells of the grid. Each box is a cube with equal dimensions, which match exactly the dimensions of a cell of the grid.

However, Barbara soon realizes that it may be dangerous for the rabbit to make jumps of height greater than $1$ box, so she decides to avoid that by making some adjustments to the house. For every pair of adjacent cells, Barbara would like that their absolute difference in height be at most $1$ box. Two cells are considered adjacent if they share a common side.

As all the boxes are superglued, Barbara cannot remove any boxes that are there initially, however she can add boxes on top of them. She can add as many boxes as she wants, to as many cells as she wants (which may be zero). Help her determine what is the minimum total number of boxes to be added so that the rabbit's house is safe.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow.

Each test case begins with a line containing two integers $R$ and $C$.

Then, $R$ lines follow, each with $C$ integers. The $j$-th integer on $i$-th line, $G_{i,j}$, represents how many boxes are there initially on the cell located at the $i$-th row and $j$-th column of the grid.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from $1$) and $y$ is the minimum number of boxes to be added so that the rabbit's house is safe.

## 样例

### 样例输入 1
```
3
1 3
3 4 3
1 3
3 0 0
3 3
0 0 0
0 2 0
0 0 0
```

### 样例输出 1
```
Case #1: 0
Case #2: 3
Case #3: 4
```

## 提示

In Sample Case #$1$, the absolute difference in height for every pair of adjacent cells is already at most $1$ box, so there is no need to add any extra boxes.

In Sample Case #$2$, the absolute difference in height of the left-most cell and the middle cell is $3$ boxes. To fix that, we can add $2$ boxes to the middle cell. But then, the absolute difference of the middle cell and the right-most cell will be $2$ boxes, so Barbara can fix that by adding $1$ box to the right-most cell. After adding these $3$ boxes, the safety condition is satisfied.

In Sample Case #$3$, the cell in the middle of the grid has an absolute difference in height of $2$ boxes with all of its $4$ adjacent cells. One solution is to add exactly $1$ box to all of the middle's adjacent cells, so that the absolute difference between any pair of adjacent cells will be at most $1$ box. That requires $4$ boxes in total.

### Limits

$1 \le T \le 100$.

$0 \le G_{i,j} \le 2 \cdot 10^6$, for all $i$, $j$.

**Test Set $1$**

$1 \le R, C \le 50$.

**Test Set $2$**

$1 \le R, C \le 300$.

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

    vector<int> houses(n);
    for (int i = 0; i < n; i++) cin >> houses[i];

    int maxH = *max_element(houses.begin(), houses.end());
    cout << maxH << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
给定 $R \times C$ 的网格，每个格子有若干个盒子。只能添加盒子不能移除。要求任意相邻格子（上下左右）的高度差不超过 $1$。求最小添加盒子数。

关键约束：$R, C \le 300$，$G_{i,j} \le 2 \cdot 10^6$。

### 核心思路
高度差约束是双向的：如果一个格子很高，它的邻居必须至少为 $h-1$。因此，高度信息会从高处向低处"传播"。使用优先队列（大根堆）从最高格子开始处理：对于当前最高格子的每个邻居，若其高度低于 $h-1$，则需要添加盒子使其升高到 $h-1$，并将更新后的邻居加入堆中继续传播。

### 算法流程
1. 将所有格子的初始高度放入优先队列（大根堆）
2. 从堆中取出最高格子 $(i, j)$，高度为 $h$
3. 检查其上下左右四个邻居：
   - 若邻居高度 $< h-1$，添加 $(h-1) - \text{邻居高度}$ 个盒子，更新邻居高度为 $h-1$
   - 将更新后的邻居加入堆
4. 重复步骤 2-3 直到堆为空
5. 输出总添加盒子数

### 复杂度分析
- 时间复杂度：$O(RC \log(RC))$，每个格子最多被处理常数次，每次操作涉及堆的插入和删除
- 空间复杂度：$O(RC)$，用于存储网格和优先队列
