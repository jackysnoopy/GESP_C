# [GCJ 2014 Qualification] Deceitful War

## 题目描述

This problem is the hardest problem to understand in this round. If you are new to Code Jam, you should probably try to solve the other problems first.

Naomi and Ken sometimes play games together. Before they play, each of them gets $N$ identical-looking blocks of wood with masses between $0.0\, \text{kg}$ and $1.0\, \text{kg}$ (exclusive). All of the blocks have different weights. There are lots of games they could play with those blocks, but they usually play something they call War. Here is how War works:

1. Each player weighs each of his or her own blocks, so each player knows the weights of all of his or her own blocks, but not the weights of the other player's blocks.
2. They repeat the following process $N$ times:
    1. Naomi chooses one of her own blocks, with mass $\text{chosen}_{\text{Naomi}}$.
    2. Naomi tells Ken the mass of the block she chose.
    3. Ken chooses one of his own blocks, with mass $\text{chosen}_{\text{Ken}}$.
    4. They each put their block on one side of a balance scale, and the person whose block is heavier gets one point.
    5. Both blocks are destroyed in a fire.

Naomi has realized three things about War. First, she has realized that she loses a lot. Second, she has realized that there is a unique strategy that Ken can follow to maximize his points without assuming anything about Naomi's strategy, and that Ken always uses it. Third, she has realized that she hates to lose. Naomi has decided that instead of playing War, she will play a game she calls Deceitful War. The great thing about Deceitful War is that Ken will think they're playing War!

Here is how Deceitful War works, with differences between Deceitful War and War in bold:

1. Each player weighs each of his or her own blocks. **Naomi also weighs Ken's blocks while he isn't looking, so Naomi knows the weights of all blocks and Ken only knows the weights of his own blocks.**
2. They repeat the following process $N$ times:
    1. Naomi chooses one of her own blocks, with mass $\text{chosen}_{\text{Naomi}}$.
    2. **Naomi tells Ken a number, $\text{Told}_{\text{Naomi}}$, between $0.0\, \text{kg}$ and $1.0\, \text{kg}$ exclusive. Ken, who thinks they're playing War, thinks the number Naomi just told him is $\text{chosen}_{\text{Naomi}}$.**
    3. Ken chooses one of his own blocks, with mass $\text{chosen}_{\text{Ken}}$.
    4. They each put their block on one side of a balance scale, and the person whose block is heavier gets one point.
    5. Both blocks are destroyed in a fire.

Naomi doesn't want Ken to know that she isn't playing War; so when she is choosing which block to play, and what mass to tell Ken, she must make sure that the balance scale won't reveal that $\text{Chosen}_{\text{Naomi}} \neq \text{Told}_{\text{Naomi}}$. In other words, she must make decisions so that:

* $\text{Chosen}_{\text{Naomi}} > \text{Chosen}_{\text{Ken}}$ if, and only if, $\text{Told}_{\text{Naomi}} > \text{Chosen}_{\text{Ken}}$, and
* $\text{Told}_{\text{Naomi}}$ is not equal to the mass of any of Ken's blocks, because he knows that isn't possible.

It might seem like Naomi won't win any extra points by being deceitful, because Ken might discover that she wasn't playing War; but Naomi knows Ken thinks both players are playing War, and she knows what he knows, and she knows Ken will always follow his unique optimal strategy for War, so she can always predict what he will play.

You'll be given the masses of the blocks Naomi and Ken started with. Naomi will play Deceitful War optimally to gain the maximum number of points. Ken will play War optimally to gain the maximum number of points assuming that both players are playing War. What will Naomi's score be? What would it have been if she had played War optimally instead?

**Examples**

If each player has a single block left, where Naomi has $0.5\, \text{kg}$ and Ken has $0.6\, \text{kg}$, then Ken is guaranteed to score the point. Naomi can't say her number is $\geq 0.6\, \text{kg}$, or Ken will know she isn't playing War when the balance scale shows his block was heavier.

If each player has two blocks left, where Naomi has $[0.7\, \text{kg}, 0.2\, \text{kg}]$ and Ken has $[0.8\, \text{kg}, 0.3\, \text{kg}]$, then Naomi could choose her $0.2\, \text{kg}$ block, and deceive Ken by telling him that she chose a block that was $0.6\, \text{kg}$. Ken assumes Naomi is telling the truth (as in how the War game works) and will play his $0.8\, \text{kg}$ block to score a point. Ken was just deceived, but he will never realize it because the balance scale shows that his $0.8\, \text{kg}$ block is, like he expected, heavier than the block Naomi played. Now Naomi can play her $0.7\, \text{kg}$ block, tell Ken it is $0.7\, \text{kg}$, and score a point. If Naomi had played War instead of Deceitful War, then Ken would have scored two points and Naomi would have scored zero.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing a single integer $N$, the number of blocks each player has. Next follows a line containing $N$ space-separated real numbers: the masses of Naomi's blocks, in kg. Finally there will be a line containing $N$ space-separated real numbers: the masses of Ken's blocks, in kg.

Each of the masses given to Ken and Naomi will be represented as a $0$, followed by a decimal point, followed by $1$-$5$ digits. Even though all the numbers in the input have $1$-$5$ digits after the decimal point, Ken and Naomi don't know that; so Naomi can still tell Ken that she played a block with mass $0.5000001\, \text{kg}$, and Ken has no reason not to believe her.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$ $z$", where $x$ is the test case number (starting from $1$), $y$ is the number of points Naomi will score if she plays Deceitful War optimally, and $z$ is the number of points Naomi will score if she plays War optimally.

## 样例

### 样例输入 1
```
4
1
0.5
0.6
2
0.7 0.2
0.8 0.3
3
0.5 0.1 0.9
0.6 0.4 0.3
9
0.186 0.389 0.907 0.832 0.959 0.557 0.300 0.992 0.899
0.916 0.728 0.271 0.520 0.700 0.521 0.215 0.341 0.458
```

### 样例输出 1
```
Case #1: 0 0
Case #2: 1 0
Case #3: 2 1
Case #4: 8 4
```

## 提示

**Limits**

- $1 \leq T \leq 50$.
- All the masses given to Ken and Naomi are distinct, and between $0.0$ and $1.0$ exclusive.

**Small dataset**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq N \leq 10$.

**Large dataset**

- Time limit: ~~120~~ 5 seconds.
- $1 \leq N \leq 1000$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<double> naomi(N), ken(N);
        for (int i = 0; i < N; i++) cin >> naomi[i];
        for (int i = 0; i < N; i++) cin >> ken[i];

        sort(naomi.begin(), naomi.end());
        sort(ken.begin(), ken.end());

        int deceit = 0, war = 0;

        int i = 0, j = 0;
        while (i < N && j < N) {
            if (naomi[i] > ken[j]) {
                deceit++;
                j++;
            }
            i++;
        }

        i = 0, j = 0;
        while (i < N && j < N) {
            if (ken[j] > naomi[i]) {
                war++;
                i++;
            }
            j++;
        }

        cout << "Case #" << t << ": " << deceit << " " << N - war << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析

Naomi 和 Ken 各有 N 个木块。在 War 模式下，Naomi 公布自己木块的真实质量，Ken 选择最优策略应对。在 Deceitful War 模式下，Naomi 可以谎报质量（但必须保证天平结果与谎报一致），Ken 仍按 War 的最优策略应对。需要分别求出两种模式下 Naomi 的最高得分。

### 核心思路

**Deceitful War**：Naomi 知道 Ken 的所有木块质量，可以用最小的木块"骗"Ken 出最大的木块。贪心策略是：将双方木块排序后，用双指针从最小开始匹配，若 Naomi 当前最小木块能赢 Ken 当前最小木块，则得分并消耗 Ken 的该木块；否则丢弃 Naomi 的最小木块（用于"骗"Ken 的大木块）。

**War**：Ken 知道 Naomi 的策略后会用最优应对。贪心策略是：Ken 用自己最小的能赢 Naomi 当前木块的木块去应对。统计 Ken 能赢的回合数 war，则 Naomi 得分为 N - war。

### 算法流程

1. 读入并排序 Naomi 和 Ken 的木块质量数组。
2. **Deceitful War 计算**：双指针 i=0, j=0 从最小开始。若 naomi[i] > ken[j]，则 deceit++ 且 j++；始终 i++。最终 deceit 即为 Deceitful War 得分。
3. **War 计算**：双指针 i=0, j=0 从最小开始。若 ken[j] > naomi[i]，则 war++ 且 i++；始终 j++。War 得分为 N - war。
4. 输出两个得分。

### 复杂度分析

- 时间复杂度：O(T × N log N)，排序为主，双指针遍历为 O(N)。
- 空间复杂度：O(N)，用于存储两个数组。
