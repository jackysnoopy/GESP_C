# [USACO23JAN] Moo Operations B

## 题目描述

Because Bessie is bored of playing with her usual text string where the only characters are `C`, `O`, and `W`, Farmer John gave her $Q$ new strings $(1 \le Q \le 100)$, where the only characters are `M` and `O`. Bessie's favorite word out of the characters `M` and `O` is obviously `MOO`, so she wants to turn each of the $Q$ strings into `MOO` using the following operations:

1. Replace either the first or last character with its opposite (so that 'M' becomes 'O' and 'O' becomes 'M').
2. Delete either the first or last character. 

Unfortunately, Bessie is lazy and does not want to perform more operations than absolutely necessary. For each string, please help her determine the minimum number of operations necessary to form `MOO` or output $−1$ if this is impossible.

## 输入格式

The first line of input contains the value of $Q$.

The next $Q$ lines of input each consist of a string, each of its characters either `M` or `O`. Each string has at least $1$ and at most $100$ characters.

## 输出格式

Output the answer for each input string on a separate line.

## 样例

### 样例输入1
```3
MOMMOM
MMO
MOO
```

### 样例输出1
```4
-1
0
```

## 提示

### Explanation for Sample 1

A sequence of $4$ operations transforming the first string into `MOO` is as follows:

Replace the last character with `O` (operation 1)  
Delete the first character (operation 2)  
Delete the first character (operation 2)  
Delete the first character (operation 2)  

The second string cannot be transformed into `MOO`. The third string is already `MOO`, so no operations need to be performed. 

### Scoring

 - Inputs $2-4$: Every string has length at most $3$.
 - Inputs $5-11$: No additional constraints.

## 解题思路

### 问题分析
字符串只含M和O，通过替换首尾字符或删除首尾字符，最少操作变MOO。

### 核心思路
枚举MOO三个字符在原串中的位置(i,j,k)，j=k-1。计算变换成本=n-3+替换次数。

### 算法流程
1. 枚举i和k（k=i+2到n-1）
2. M在i, O在k-1, O在k
3. 计算替换次数+n-3

### 复杂度分析
时间O(N^2)，空间O(1)。
