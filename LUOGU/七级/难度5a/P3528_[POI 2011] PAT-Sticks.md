# P3528 [POI 2011] PAT-Sticks

## 题目描述

Little Johnny was given a birthday present by his grandparents.

This present is a box of sticks of various lengths and colours.

Johnny wonders if there are three sticks in the set he has been given that would form a triangle with different-coloured sides.

Let us note that Johnny is interested in non-degenerate triangles only, i.e., those with positive area.

## 输入格式

In the first line of the standard input an integer $k$ ($3\le k\le 50$) is given, which is the number of different colours of sticks.

The following $k$ lines contain descriptions of the sticks of particular colours.

## 输出格式

Your program should print (on the first and only line of the standard output) either:
- six integers, separated by single spaces, that describe the construction of a triangle with different-coloured sides
- or the word NIE (Polish for no) if no such triple of sticks exists.

## 样例

### 样例1
**输入：**
```
4
1 42
2 6 9
3 8 4 8
1 12
```

**输出：**
```
3 8 4 12 2 9
```

## 解题思路

这是一道几何+贪心的题目。

**算法**：
1. 将所有棍子按长度排序
2. 检查相邻的三个不同颜色的棍子是否能组成三角形
3. 如果能，输出结果；否则输出NIE

**时间复杂度**：$O(N \log N)$

## 相关题目

- 三角形不等式
- 贪心算法
