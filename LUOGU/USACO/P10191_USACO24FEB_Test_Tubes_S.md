# [USACO24FEB] Test Tubes S

## 题目描述

Bessie has recently gotten into chemistry. At the moment, she has two different colors $1$ and $2$ of various liquids that don't mix well with one another. She has two test tubes of infinite capacity filled with $N$ $(1 \leq N \leq 10^5)$ units each of some mixture of liquids of these two colors. Because the liquids don't mix,  once they settled, they divided into layers of separate colors. Because of this, the two tubes can be viewed as strings $f_1f_2\ldots f_N$ and $s_1s_2\ldots s_N$  where $f_i$ represents the color of the liquid that is $i$ units from the bottom of the first tube, and $s_i$ represents the color of the liquid that is $i$ units from the bottom of the second tube. It is guaranteed that there is at least one unit of each color of liquid.  

Bessie wants to separate these liquids so that each test tube contains all units of one color of liquid. She has a third empty beaker of infinite capacity to help her in this task. When Bessie makes a "pour", she moves all liquid of color $i$ at the top of one test tube or beaker into another.  

Determine the minimum number of pours to separate all the liquid into the two test tubes, and the series of moves needed to do so. It does not matter which test tube ends up with which color, but the beaker must be empty..  

There will be $T$ ($1 \leq T \leq 10$) test cases, with a parameter $P$ for each test case.  

Suppose the minimum number of pours to separate the liquids into the original tubes is $M$.  


- If $P=1$, you will receive credit if you print only $M$.
- If $P=2$, you will receive credit if you print an integer $A$ such that $M \leq A \leq M+5$, followed by $A$ lines that construct a solution with that number of moves. Each line should contain the source and the destination tube ($1$, $2$, or $3$ for the beaker). The source tube must be nonempty before the move and a tube may not be poured into itself.
- If $P=3$, you will receive credit if you print $M$, followed by a valid construction using that number of moves.

## 样例

--- Sample 1 ---
Input:
6
4 1
1221
2211
4 2
1221
2211
4 3
1221
2211
6 3
222222
111112
4 3
1121
1222
4 2
1121
1222
Output:
4
4
1 2
1 3
2 1
3 2
4
1 2
1 3
2 1
3 2
1
2 1
5
2 3
1 2
1 3
1 2
3 1
6
2 3
1 2
1 3
1 2
2 1
3 2

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
