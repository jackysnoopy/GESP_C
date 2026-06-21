# [SCCPC 2021] Rock Paper Scissors

## 题目描述

BaoBao and DreamGrid are playing a card game. Each player has $n$ cards in the beginning and there are three types of cards: rock, paper, and scissors.

The game consists of $n$ rounds. In each round, BaoBao will first play one of his remaining cards (this card is shown to both players). After that, DreamGrid can choose one of his remaining cards and play it (also shown to both players). The score of this round is calculated by referring to the following table:

$$
\begin{array}{|c|c|c|c|}
\hline
\text{DreamGrid} \downarrow \,\,\,\, \text{BaoBao} \rightarrow & \textbf{Rock} & \textbf{Paper} & \textbf{Scissors} \\
\hline
\textbf{Rock} & 0 & -1 & 1 \\
\hline
\textbf{Paper} & 1 & 0 & -1 \\
\hline
\textbf{Scissors} & -1 & 1 & 0\\
\hline
\end{array}
$$

After the round, the two played cards are removed from the game. The score of the whole game is the sum of the score of each round.

BaoBao aims at minimizing the score of the whole game, while DreamGrid aims at maximizing it. Both players know the number of cards of each type his opponent and himself holds in the beginning. What's the final score of the game given that both of them take the best strategy?

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 10^3$) indicating the number of test cases. For each test case:

The first line contains three integers $b_r$, $b_p$ and $b_s$ ($0 \le b_r, b_p, b_s \le 10^9$), indicating the number of rock, paper and scissors cards BaoBao has.

The second line contains three integers $d_r$, $d_p$ and $d_s$ ($0 \le d_r, d_p, d_s \le 10^9$), indicating the number of rock, paper and scissors cards DreamGrid has.

It's guaranteed that $b_r + b_p + b_s = d_r + d_p + d_s$.

## 输出格式

For each test case output one line containing one integer indicating the final score of game.

## 样例

### 样例输入1
```4
4 4 2
10 0 0
0 10 0
2 4 4
1 2 3
3 2 1
10 10 10
10 10 10
```

### 样例输出1
```-2
2
5
30
```

## 提示



## 解题思路

### 问题分析

石头剪刀布博弈，先手后手最优策略。

### 核心思路

DreamGrid先赢后输：先用克制牌赢，再被迫输。

### 算法流程

1. 计算DreamGrid最大赢局数W
2. 用剩余牌计算被迫输局数L'
3. 答案=W-L'

### 复杂度分析

O(1)时间，O(1)空间。
