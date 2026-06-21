# [GCJ 2014 #2] Data Packing

## 题目描述

Adam, being a well-organized man, has always been keenly interested in organizing all his stuff. In particular, he fondly remembers the many hours of his youth that were spent moving files from his computer onto Compact Discs.

There were two very important rules involved in this procedure. First, in order to ensure that all discs could be labeled clearly, Adam would never place more than two files on the same disc. Second, he would never divide a single file over multiple discs. Happily, the discs he was using were always large enough to make this possible.

Thinking back, Adam is now wondering whether he arranged his files in the best way, or whether he ended up wasting some Compact Discs. He will provide you with the capacity of the discs he used (all his discs had the same capacity) as well as a list of the sizes of the files that he stored. Please help Adam out by determining the minimum number of discs needed to store all his files—following the two very important rules, of course.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing two integers: the number of files to be stored $N$, and the capacity of the discs to be used $X$ (in MBs). The next line contains the $N$ integers representing the sizes of the files $S_i$ (in MBs), separated by single spaces.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the minimum number of discs needed to store the given files.

## 样例

### 样例输入1
```3
3 100
10 20 70
4 100
30 40 60 70
5 100
10 20 30 40 60
```

### 样例输出1
```Case #1: 2
Case #2: 2
Case #3: 3
```

## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq X \leq 700$.
- $1 \leq S_i \leq X$.

**Small dataset(5 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq N \leq 10$.

**Large dataset(8 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leq N \leq 10^4$.

## 解题思路

### 问题分析

最少光盘数存储文件，每盘最多2个文件。

### 核心思路

贪心双指针：最大+最小配对。

### 算法流程

1. 排序文件大小
2. 双指针：最小+最大<=容量则配对，否则最大单独放

### 复杂度分析

O(n log n)时间，O(n)空间。
