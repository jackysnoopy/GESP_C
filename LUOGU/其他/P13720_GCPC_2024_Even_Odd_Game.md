# [GCPC 2024] Even Odd Game

## 题目描述

As every Saturday, Eve is paying her local game club a visit.
Today, Bob has brought a new game he has designed on his own.
After thorough investigation, you claim that there exists a dominant strategy, so one player can always win.
Bob is hesitant to accept that his game is boring to play, so he challenges you to play a round!
Since you claim that there exists a dominant strategy, you may determine who begins the game.

![](https://cdn.luogu.com.cn/upload/image_hosting/119eym2b.png)

:::align{center}
Figure E.1: The cards in the two sample interactions.
:::

The rules are as follows.
There are $n$ cards on the table, each containing a maths operation ($\texttt{+}$ or $\texttt{*}$) and an integer, as shown in Figure E.1.
Eve and Bob alternate picking cards to manipulate a common number using one of the cards.
For instance, if the current value of the number is $5$, and the card says $+3$, then the value gets updated to $8$.
Each card can only be used once, and the game ends when all the cards have been used.
The player who makes the first move wins if the final number is odd, and the other player wins if the final number is even.
Given the list of cards and the starting value, help Eve win the game.

## 样例

--- Sample 1 ---
Input:
3
+ 7
* 4
+ 2
1


* 4
Output:





me
+ 2

+ 7
--- Sample 2 ---
Input:
2
+ 8
* 5
10

+ 8
Output:




you

* 5

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
