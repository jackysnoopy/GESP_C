# P3507 [POI 2010] GRA-The Minima Game

## 题目描述

Alice and Bob learned the minima game, which they like very much, recently.

The rules of the game are as follows.

A certain number of cards lies on a table, each inscribed with a positive integer.

The players make alternate moves, Alice making the first one.

A move consists in picking an arbitrary positive number of cards from the table.

For such move the player receives a number of points equal to the minimum of the numbers inscribed on the cards he collected.

The game ends when the last card is removed from the table.

The goal of each player is maximizing the difference between their and their opponent's score.

## 输入格式

In the first line of the standard input there is one integer $n$ ($1 \le n \le 10^6$), denoting the number of cards.

The second line holds $n$ positive integers $a_i$ ($1 \le a_i \le 10^6$), separated by single spaces, that are inscribed on the cards.

## 输出格式

Your program should print out a single line with a single integer to the standard output - the number of points by which Alice wins over Bob, assuming they both play optimally.

## 样例

### 样例1
**输入：**
```
3
1 3 1
```

**输出：**
```
2
```

## 解题思路

这是一道博弈论题目，可以使用DP解决。

**算法**：
1. 将数字排序
2. 使用DP计算最优差值
3. 考虑每个数字是否被选中

**时间复杂度**：$O(n^2)$

## 相关题目

- 博弈论
- 动态规划
