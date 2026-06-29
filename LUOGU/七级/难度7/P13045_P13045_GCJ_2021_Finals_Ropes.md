# P13045 [GCJ 2021 Finals] Ropes

## 题目描述

Two scout teams are taking part in a scouting competition. The game is played along a river with $4 \mathrm{~N}$ trees planted along the river, with exactly $2 \mathrm{~N}$ of them lined up along the north bank and $2 \mathrm{~N}$ lined up along the south bank.

On each turn, the playing team selects one tree on each bank that does not have any ropes tied to it and ties a rope between both trees, making it cross the river. Each rope that is added is placed higher than all previous ropes. The playing team scores 1 point per each previously used rope that passes below the newly added rope.

After $2 \mathrm{~N}$ turns, all trees have exactly one rope tied to them, so there are no more possible plays and the game is over.

## 输入格式

初始读入三个整数 $\mathbf{T}, \mathbf{N}$, 和 $\mathbf{W}$。

对于每个测试用例，需要进行 $\mathbf{N}$ 次交互。

## 输出格式

每次交互输出两个整数 $\mathbf{A}_{i}$ 和 $\mathbf{B}_{i}$，表示连接的树的位置。

## 样例

### 样例1
输入：
```
1 2 1
```
输出：
```
1 2
2 1
```

## 提示

这是交互题。

## 解题思路

### 问题分析

这是一个交互博弈问题。需要与对手进行游戏。

### 核心思路

**贪心策略**：尽量连接对称位置的树。

### 算法流程

```
对于每个测试用例:
    对于每回合:
        输出连接的树
        读取对手的移动
```

### 复杂度分析

- **时间复杂度**：$O(T \cdot N)$
- **空间复杂度**：$O(1)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, N, W;
    cin >> T >> N >> W;
    
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < N; i++) {
            int A = i + 1;
            int B = N - i;
            cout << A << " " << B << endl;
            
            int C, D;
            cin >> C >> D;
        }
    }
    
    return 0;
}
```
