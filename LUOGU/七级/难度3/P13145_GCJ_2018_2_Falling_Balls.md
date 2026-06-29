# [GCJ 2018 #2] Falling Balls

## 题目描述

A certain toy consists of a grid of 2 or more columns and 1 or more rows, where each cell of the grid contains either a $\backslash$ ramp or a $/$ ramp, or is empty. The leftmost and rightmost columns are empty and the bottom row is also empty. Balls are dropped into the top row and fall vertically, sliding on ramps. To prevent balls from getting stuck, a cell with a $\backslash$ ramp is never immediately to the left of a cell with a $/$ ramp.

When a ball is dropped into the top row, it moves deterministically as follows:

* A ball in an empty cell moves to the cell immediately below its current cell, unless it is in the bottom row, in which case it does not move any more.
* A ball in a cell containing a $\backslash$ ramp moves to the cell immediately below and to the right of its current cell.
* A ball in a cell containing a $/$ ramp moves to the cell immediately below and to the left of its current cell.

To see the mechanism to its full extent, the user drops exactly one ball into each column. Balls do not interfere with each other, and it is possible for a cell to contain multiple balls.

Your friend has a toy with $C$ columns and an unknown number of rows. They just dropped one ball into the top row of each column, and waited for all balls to stop moving. Then, they counted how many balls ended up in each of the cells of the bottom row, and gave you those results... but you think it is possible that they made a mistake. Can you create a layout that is consistent with the results and uses as few rows as possible, or determine that no such layout exists?

For example, if your friend reported the values $3 \ 0 \ 0 \ 2 \ 0 \ 1$, one possible solution would be the following. (Note that it is not necessary to use a minimal number of ramps, or for every ramp to affect the balls.)

```
./\\...
./\.\/.
.......
```

Here are the paths that the balls would take when falling through that grid:

![](https://cdn.luogu.com.cn/upload/image_hosting/ia5vs05s.png)

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line containing an integer $C$: the number of columns in your friend's falling ball toy. Then, there is one more line containing $C$ integers $B_i$. The i-th of these integers represents the number of balls that ended up in the i-th cell from the left of the bottom row of your friend's falling ball toy, according to the data they gave you.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is either IMPOSSIBLE, or the number of rows in your layout, as described above. If $y$ is not IMPOSSIBLE, output $y$ more rows, representing the rows of your proposed falling ball toy layout, in order from top to bottom. Use . to represent a cell with no ramp, and $\backslash$ or $/$ to represent the ramps. The layout must obey all of the rules in the problem statement.

## 样例

### 样例输入 1
```
3
4
1 1 1 1
3
0 2 1
6
3 0 0 2 0 1
```

### 样例输出 1
```
Case #1: 1
....
Case #2: IMPOSSIBLE
Case #3: 3
.//\..
./\./.
......
```

## 提示

**Sample Explanation**

Note that the last sample case would not appear in Test set 1.

The following layout is the only valid solution for Sample Case #1. (There must be at least one row, and including any more rows would make the solution use more rows than needed. It is not legal to include any ramps in the bottom row.)

```
....
```
In Sample Case #2, there is no way to prevent the leftmost ball from falling to the bottom of its column without adding a ramp, but ramps cannot be added to that column.

Sample Case #3 is the one described at the end of the problem statement. Note that the following invalid layout for Sample Case #3 breaks several rules: it has more rows than needed, it has ramps in the three illegal zones (left column, right column, bottom row), and it contains a $\backslash$ ramp immediately to the left of a $/$ ramp.

```
\\..\/
../.\/
./../.
..../.
```

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq B_i \leq C$, for all $i$.
- The sum (over all $i$ from 1 to $C$, inclusive) of all $B_i$ values = $C$.

## 解题思路

### 问题分析

给定 $C$ 列的弹球装置，每个格子可以是 `\`（向右下）、`/`（向左下）或空。从每列顶部放入一个球，求使球到达指定底部位置的最少行数，或判断不可能。

### 核心思路

**关键观察**：球在每一行最多水平移动 1 格。若第 $i$ 个球需要从列 $i$ 移动到列 $target[i]$，则至少需要 $|target[i] - i|$ 行。因此最少行数为 $\max_i |target[i] - i| + 1$（加 1 是因为最后一行必须为空）。

**可行性判断**：若 $B[1] = 0$ 或 $B[C] = 0$，则不可能——最左/最右列的球无法被引导到其他列（边界列无法放斜坡）。

**构造方案**：贪心逐行放置斜坡，使球逐步向目标列移动。

### 算法流程

1. 检查 $B[1]$ 和 $B[C]$ 是否为 0，若是则输出 IMPOSSIBLE
2. 将 $B$ 数组展开为每个球的目标列 $target[i]$
3. 计算最大移动距离 $maxDist = \max |target[i] - i|$
4. 逐行构造网格：每行确定每个位置需要的斜坡方向
5. 输出行数和网格

### 复杂度分析

- **时间复杂度**：$O(C \times maxDist)$，最坏 $O(C^2)$
- **空间复杂度**：$O(C \times maxDist)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int C;
        cin >> C;
        vector<int> B(C + 1);
        for (int i = 1; i <= C; i++) cin >> B[i];
        if (B[1] == 0 || B[C] == 0) {
            cout << "Case #" << tc << ": IMPOSSIBLE\n";
            continue;
        }
        vector<int> target(C + 1);
        int ball = 0;
        for (int col = 1; col <= C; col++) {
            for (int j = 0; j < B[col]; j++) { ball++; target[ball] = col; }
        }
        int maxDist = 0;
        for (int i = 1; i <= C; i++) maxDist = max(maxDist, abs(target[i] - i));
        int numRows = maxDist + 1;
        vector<int> pos(C + 1);
        for (int i = 1; i <= C; i++) pos[i] = i;
        vector<string> rows;
        for (int r = 0; r < maxDist; r++) {
            string row(C, '.');
            for (int j = 2; j <= C - 1; j++) {
                bool needRight = false, needLeft = false;
                for (int i = 1; i <= C; i++) {
                    if (pos[i] == j) {
                        if (target[i] > j) needRight = true;
                        else if (target[i] < j) needLeft = true;
                    }
                }
                if (needRight) row[j - 1] = '\\';
                else if (needLeft) row[j - 1] = '/';
            }
            rows.push_back(row);
            vector<int> newPos = pos;
            for (int i = 1; i <= C; i++) {
                if (row[pos[i] - 1] == '\\') newPos[i] = pos[i] + 1;
                else if (row[pos[i] - 1] == '/') newPos[i] = pos[i] - 1;
            }
            pos = newPos;
        }
        rows.push_back(string(C, '.'));
        cout << "Case #" << tc << ": " << numRows << "\n";
        for (string& row : rows) cout << row << "\n";
    }
    return 0;
}
```
