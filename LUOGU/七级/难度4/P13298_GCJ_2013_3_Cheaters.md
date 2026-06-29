# [GCJ 2013 #3] Cheaters

## 题目描述

You've been playing roulette for a while in a local casino. Roulette is a simple casino game in which multiple players place bets on one or more numbers between 0 and 36 (inclusive). Next, a wheel is spun in one direction with a ball spinning in the other direction. The roulette wheel contains the same numbers 0 to 36. Some real roulette wheels also have a space labeled 00, but ours does not. Eventually, the ball falls on one of the numbers. If a player placed a bet on that particular number, he receives 36 times his bet (so the profit of that bet is 35 times the bet). All bets placed on other numbers lose.

Unfortunately, luck hasn't been on your side, and you have been losing all night long. At one point, you started to wonder whether the roulette game was fair or not, and after observing the game some more, you noticed a pattern that must be profitable for the casino: the ball always lands on one of the numbers that has the least total money bet on it! If multiple numbers tie for the least total money bet, the ball lands on one of those uniformly at random.

Of course, you'll be notifying the authorities about this foul play, but first you want to win your money back by exploiting your new-found knowledge. To do so, you wait until all other players have placed their bets and then place bets of your own. Unfortunately, you have a limited budget left, so you cannot bet more than that. You are allowed to bet on zero or more different numbers, and each of those bets can be any positive integer amount (perhaps with different amounts for different numbers), so as long as the sum of your bets does not exceed your budget. What is the maximum expected profit you can make?

## 输入格式

The first line of input gives the number of cases, $T$. $T$ test cases follow. Each test case consists of two lines. The first line contains two integers: the budget you still have, $B$, and the number of numbers other players have placed bets on, $N$. The second line contains $N$ integers $X_i$, the total amounts of money bet by other players on each of those different numbers.

## 输出格式

For each test case, output one line containing "Case #x: " followed by the maximum expected profit that you make if you place your bets optimally. A profit will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.

## 样例

### 样例输入 1
```
3
100 1
10
34 3
5 6 7
34 4
1 1 10 10
```

### 样例输出 1
```
Case #1: 0
Case #2: 2
Case #3: 0.9428571429
```

## 提示

**Sample Explanation**

In example $2$, bet $1$ on each of the $34$ empty numbers for a guaranteed payback of $36$, and a profit of $36 - 34 = 2$. In example $3$, bet $1$ on each of the $33$ empty numbers, so that you win 36 with probability $33/35$. The gives an expected profit of $33/35 \times 36 - 33$.

**Limits**

- $1 \leq T \leq 100.$
- $1 \leq N \leq 37.$

**Small dataset (7 Pts, Test set 1 - Visible)**

- $1 \leq B, X_i \leq 1,000.$

**Large dataset (10 Pts, Test set 2 - Hidden)**

- $1 \leq B, X_i \leq 10^{12}.$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        long long B;
        cin >> B >> N;

        vector<long long> X(N);
        for (int i = 0; i < N; i++) cin >> X[i];

        long long total_other = 0;
        for (int i = 0; i < N; i++) total_other += X[i];

        long long empty = 37 - N;

        if (empty == 0) {
            cout << "Case #" << t << ": 0\n";
            continue;
        }

        double prob = (double)empty / 37.0;
        double expected = prob * 36.0;

        long long bet = min(B, (long long)empty);
        double profit = expected * bet - bet;

        cout << "Case #" << t << ": " << fixed << setprecision(10) << profit << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
轮盘赌游戏中，球总是落在投注总额最少的数字上。已知其他玩家的投注分布，你在观察后用有限预算投注，求最大期望利润。

共有 37 个数字（0~36），未被投注的数字即为"空位"，球将以均等概率落在其中一个空位上。

### 核心思路
由于球总是落在投注最少的数字上，最优策略是在所有空位上各投注 1 单位（因为每个空位的投注额都是 0，是全局最少的）。设空位数量为 `empty`，则：
- 球落在空位的概率为 `empty / 37`
- 若命中，收益为 36（赔付 36 倍投注额）
- 期望收益 = `(empty / 37) × 36 × bet - bet`

由于 `36 × empty / 37 > 1` 当 `empty ≥ 1` 时，期望利润为正，应尽量多投注。预算上限为 `B`，空位数量为 `37 - N`，实际投注量为 `min(B, 37 - N)`。

### 算法流程
1. 统计其他玩家投注的数字数量 `N`，计算空位数 `empty = 37 - N`
2. 若无空位，输出 0
3. 计算期望单次收益 `expected = (empty / 37) × 36`
4. 确定投注量 `bet = min(B, empty)`
5. 输出期望利润 `profit = expected × bet - bet`

### 复杂度分析
- **时间复杂度**：$O(N)$，单次遍历统计投注
- **空间复杂度**：$O(N)$，存储投注数组
