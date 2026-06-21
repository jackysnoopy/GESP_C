# [USACO09MAR] Sand Castle S

## 题目描述

Farmer John has built a sand castle! Like all good castles, the walls have crennelations, that nifty pattern of embrasures (gaps) and merlons (filled spaces); see the diagram below. The N (1 <= N <= 25,000) merlons of his castle wall are conveniently numbered 1..N; merlon i has height M\_i (1 <= M\_i <= 100,000); his merlons often have varying heights, unlike so many.

He wishes to modify the castle design in the following fashion: he has a list of numbers B\_1 through B\_N (1 <= B\_i <= 100,000), and wants to change the merlon heights to those heights B\_1, ..., B\_N in some order (not necessarily the order given or any other order derived from the data).

To do this, he has hired some bovine craftsmen to raise and lower the merlons' heights. Craftsmen, of course, cost a lot of money. In particular, they charge FJ a total X (1 <= X <= 100) money per unit height added and Y (1 <= Y <= 100) money per unit height

reduced.

FJ would like to know the cheapest possible cost of modifying his sand castle if he picks the best permutation of heights. The answer is guaranteed to fit within a 32-bit signed integer.

Note: about 40% of the test data will have N <= 9, and about 60% will have N <= 18.

## 输入格式

\* Line 1: Three space-separated integers: N, X, and Y

\* Lines 2..N+1: Line i+1 contains the two space-separated integers: M\_i and B\_i

## 输出格式

\* Line 1: A single integer, the minimum cost needed to rebuild the castle

## 样例

### 样例输入1
```3 6 5 
3 1 
1 2 
1 2
```

### 样例输出1
```11
```

## 提示

FJ's castle starts with heights of 3, 1, and 1. He would like to change them so that their heights are 1, 2, and 2, in some order. It costs 6 to add a unit of height and 5 to remove a unit of height.


FJ reduces the first merlon's height by 1, for a cost of 5 (yielding merlons of heights 2, 1, and 1). He then adds one unit of height to the second merlon for a cost of 6 (yielding merlons of heights 2, 2, and 1).

## 解题思路

### 问题分析

N 个城垛高度 M_i，要变为 B 的某个排列，升高花费 X/单位，降低 Y/单位，求最小花费。

### 核心思路

排序后对应匹配：M 和 B 都排序，对应元素差值乘以对应花费。

### 算法流程

1. M 和 B 分别升序排序
2. 对应位置计算升高或降低费用
3. 累加

### 复杂度分析

时间 O(n log n)，空间 O(n)
