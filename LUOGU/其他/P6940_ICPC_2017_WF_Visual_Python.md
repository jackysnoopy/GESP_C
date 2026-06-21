# [ICPC 2017 WF] Visual Python++

## 题目描述

In the recently proposed Visual Python++ programming language, a block of statements is represented as a rectangle of characters with top-left corner in row $r_{1}$ and column $c_{1},$ and bottom-right corner in row $r_{2}$ and column $c_{2}.$ All characters at locations $(r , c)$ with $r_{1} \le r \le r_{2}$ and $c_{1} \le c \le c_{2}$ are then considered to belong to that block. Among these locations, the ones with $r = r_{1}$ or $r = r_{2}$ or $c = c_{1}$ or $c = c_{2}$ are called a border.

Statement blocks can be nested (rectangles contained in other rectangles) to an arbitrary level. In a syntactically correct program, every two statement blocks are either nested (one contained in the other) or disjoint (not overlapping). In both cases, their borders may not overlap.

Programmers are not expected to draw the many rectangles contained in a typical program $-$ this takes too long, and Visual $Pytho_n++$ would not have a chance to become the next ICPC programming language. So a programmer only has to put one character $‘p'$ in the top-left corner of the rectangle and one character $‘y'$ in the bottom-right corner. The parser will automatically match up the appropriate corners to obtain the nesting structure of the program.

Your team has just been awarded a five-hour contract to develop this part of the parser.

## 样例

--- Sample 1 ---
Input:
2
4 7
9 8
14 17
19 18

Output:
2
1

--- Sample 2 ---
Input:
2
4 7
14 17
9 8
19 18

Output:
1
2

--- Sample 3 ---
Input:
2
4 8
9 7
14 18
19 17

Output:
syntax error

--- Sample 4 ---
Input:
3
1 1
4 8
8 4
10 6
6 10
10 10

Output:
syntax error

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
