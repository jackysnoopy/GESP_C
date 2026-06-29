# [GCJ 2020 #1B] Expogo

## 题目描述

You have just received the best gift ever: an Expogo stick. You can stand on it and use it to make increasingly large jumps.

You are currently standing on point $(0,0)$ in your infinite two-dimensional backyard, and you are trying to reach a goal point $(\mathrm{X}, \mathrm{Y})$, with integer coordinates, in as few jumps as possible. You must land exactly on the goal point; it is not sufficient to pass over it on a jump.

Each time you use your Expogo stick to jump, you pick a cardinal direction: north, south, east, or west. The $i$-th jump with your Expogo stick moves you $2^{(i-1)}$ units in the chosen direction, so your first jump takes you 1 unit, your second jump takes you 2 units, your third jump takes you 4 units, and so on.

Given a goal point $(\mathrm{X}, \mathrm{Y})$, determine whether it is possible to get there, and if so, demonstrate how to do it using as few jumps as possible.

## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each consists of a single line with two integers $\mathrm{X}$ and $\mathrm{Y}$ : the coordinates of the goal point.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is IMPOSSIBLE if the goal point cannot be reached. Otherwise, $y$ must be a string of one or more characters, each of which is either $\mathrm{N}$ (north), $\mathrm{S}$ (south), $\mathrm{E}$ (east), or $\mathrm{W}$ (west), representing the directions of the jumps that you will make, in order. This sequence of jumps must reach the goal point at the end of the final jump, and it must be as short as possible.

## 样例

### 样例输入 1
```
4
2 3
-2 -3
3 0
-1 1
```

### 样例输出 1
```
Case #1: SEN
Case #2: NWS
Case #3: EE
Case #4: IMPOSSIBLE
```

## 提示

**Sample Explanation**

In Sample Case #1, you can jump south from $(0, 0)$ to $(0, -1)$, then jump east to $(2, -1)$, then jump north to $(2, 3)$.

We can be sure there is not a more efficient solution (two moves or fewer) because at least $2 + 3 = 5$ units of distance are needed to reach the goal point, but the first two jumps combined only give us $3$ units of distance.

Notice that Sample Case #2 is like Sample Case #1 but reflected across both axes, and so the answer comes from reflecting all directions in Sample Case #1's answer.

In Sample Case #3, notice that EWE would not be a valid answer, even though it reaches the target, because there is a way to get there using fewer jumps.

We leave it to you to determine why it is impossible to reach the target in Sample Case #4.

**Limits**

- $(\text{X}, \text{Y}) \neq (0, 0)$.

**Test set 1 (5 Pts, Visible Verdict)**

- $1 \leqslant \text{T} \leqslant 80$.
- $-4 \leqslant \text{X} \leqslant 4$.
- $-4 \leqslant \text{Y} \leqslant 4$.

**Test set 2 (8 Pts, Visible Verdict)**

- $1 \leqslant \text{T} \leqslant 100$.
- $-100 \leqslant \text{X} \leqslant 100$.
- $-100 \leqslant \text{Y} \leqslant 100$.

**Test set 3 (16 Pts, Visible Verdict)**

- $1 \leqslant \text{T} \leqslant 100$.
- $-10^{9} \leqslant \text{X} \leqslant 10^{9}$.
- $-10^{9} \leqslant \text{Y} \leqslant 10^{9}$.

## 解题思路

### 问题分析
给定一个无限二维网格，从(0,0)出发，第i次跳跃可以沿上下左右四个方向跳$2^{i-1}$个单位。要求用最少的跳跃次数到达目标点(X,Y)，如果无法到达则输出"IMPOSSIBLE"。

### 核心思路
利用二进制表示的性质。每次跳跃的距离是2的幂次（1, 2, 4, 8...），这类似于二进制的位权。关键观察是：
- 如果$(|X| + |Y|)$是偶数，则无法到达（因为奇偶性不匹配）
- 贪心策略：每次选择距离原点较远的坐标方向进行跳跃，跳$2^{step}$个单位，其中step是当前跳跃次数

### 算法流程
1. 读入目标坐标(X,Y)
2. 检查$(|X| + |Y|) \% 2 == 0$，如果是则输出"IMPOSSIBLE"
3. 初始化当前坐标(x,y) = (X,Y)，结果字符串ans为空
4. 当(x,y)不为(0,0)时循环：
   - 计算当前步数step = ans.size()，跳跃距离dist = 1 << step
   - 如果$|x| > |y|$：向x轴方向跳跃（x>0则'E'，否则'W'），更新x坐标
   - 否则：向y轴方向跳跃（y>0则'N'，否则'S'），更新y坐标
5. 输出结果

### 复杂度分析
- 时间复杂度：$O(\log(\max(|X|, |Y|)))$，每次跳跃坐标减半，最多跳跃约$\log_2(\max(|X|,|Y|))$次
- 空间复杂度：$O(\log(\max(|X|, | Y|)))$，用于存储结果字符串

## 参考代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int X, Y;
        cin >> X >> Y;

        cout << "Case #" << t << ": ";

        if ((abs(X) + abs(Y)) % 2 == 0) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        string ans;
        int x = X, y = Y;

        while (x != 0 || y != 0) {
            int step = ans.size();
            int dist = 1 << step;

            if (abs(x) > abs(y)) {
                if (x > 0) {
                    ans += 'E';
                    x -= dist;
                } else {
                    ans += 'W';
                    x += dist;
                }
            } else {
                if (y > 0) {
                    ans += 'N';
                    y -= dist;
                } else {
                    ans += 'S';
                    y += dist;
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
```
