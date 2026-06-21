# [UOI 2024 II Stage] Creating an Array

## 题目描述

Sofiia gave Anton an array of $\textbf{digits}$! Although this array was not the first one he had seen, he did not consider it less interesting. After playing with the array, he did not notice how he broke it to a state where he could no longer restore the original.

He was very upset because there were almost countless ways to compose the initial array. However, he remembers an interesting property of the gift: $ \sum_{i=1}^n \sum_{j=i}^n \operatorname{concat}(a_i, a_j)$, which means the sum of concatenations of all pairs of its elements, is \textbf{maximum} among all possible arrays made from these digits consisting of the same elements, as the gift.

In other words, we take all pairs of positions $i$ and $j$ such that $j$ is not to the left of $i$ ($i \le j$). And add to the sum $\overline{a_i a_j}$, where $\overline{ab}$ means the number that will result if we write the numbers $a$ and $b$ in order (or $10 \cdot a + b$). This is called the concatenation of $a$ and $b$.

For example, if Anton had an array $[1,0,3]$, then the sum would be equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $11 + 10 + 13 + 00 + 03 + 33 = 70$.

Help Anton and print an array that has this property. If there are multiple answers, any of them can be output.

## 输入格式

The first line contains $10$ integers $c_0, c_1, c_2, c_3, c_4, c_5, c_6, c_7, c_8, c_9$ ($0 \le c_i \le 50$) --- where $c_i$ corresponds to the number of digits $i$ in the initial array.

It is guaranteed that the sum of all numbers is greater than zero.

## 输出格式

Print an array consisting of $c_0 + c_1 + c_2 + c_3 + c_4 + c_5 + c_6 + c_7 + c_8 + c_9$ elements, and has the same properties as the array given by Sophia.

## 样例

### 样例输入1
```0 0 0 0 0 2 0 0 0 0
```

### 样例输出1
```5 5
```

### 样例输入2
```1 0 1 1 0 0 0 0 0 0
```

### 样例输出2
```3 2 0
```

## 提示

In the second example, there are such possible arrays:
- $[0, 2, 3]$, the sum is equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $00 + 02 + 03 + 22 + 23 + 33 = 83$;
- $[0, 3, 2]$, the sum is equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $00 + 03 + 02 + 33 + 32 + 22 = 92$;
- $[2, 0, 3]$, the sum is equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $22 + 20 + 23 + 00 + 03 + 33 = 101$;
- $[2, 3, 0]$, the sum is equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $22 + 23 + 20 + 33 + 30 + 00 = 128$;
- $[3, 0, 2]$, the sum is equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $33 + 30 + 32 + 00 + 02 + 22 = 119$;
- $[3, 2, 0]$, the sum is equal to $\overline{a_1 a_1} + \overline{a_1 a_2} + \overline{a_1 a_3} + \overline{a_2 a_2} + \overline{a_2 a_3} + \overline{a_3 a_3}$ = $33 + 32 + 30 + 22 + 20 + 00 = 137$.

## 解题思路

### 问题分析

给定数组，每次操作将一个元素加 1，求使数组非递减的最少操作数。

### 核心思路

从左到右扫描，若当前元素小于前一个，差值即为需要增加的次数。

### 算法流程

1. 对每对相邻元素 (a[i-1], a[i])
2. 若 a[i] < a[i-1]，累加 a[i-1] - a[i]

### 复杂度分析

时间 O(n)，空间 O(1)
