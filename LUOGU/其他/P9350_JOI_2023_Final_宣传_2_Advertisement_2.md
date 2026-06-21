# [JOI 2023 Final] 宣传 2 / Advertisement 2

## 题目描述

There are $N$ residents in JOI Kingdom, numbered from $1$ to $N$. Resident $i$ ($1\le i\le N$) lives at the coordinate $X_i$ on the real line, and its **power of influence** is $E_i$. It may be the case that more than one residents live at the same coordinate. A resident with a large power of influence has a high advertising potential. But such a resident is careful in buying books.

Rie published a book on informatics. In order to encourage many people to buy copies of the book, she can donate copies of the book to some residents. If she donates a copy of the book to Resident $i$ ($1\le i\le N$), Resident $i$ will get a copy of Rie’s book. Moreover, among the residents who did not yet get copies of the book, every resident $j$ ($1\le j\le N$) satisfying the following condition will buy a copy of the book and get it.

-  The distance between Resident $i$ and Resident $j$ on the real line is less than or equal to $E_i - E_j$. In other words, $|X_i − X_j| \le E_i − E_j$ is satisfied.

If all the residents read Rie’s book, the Olympiads in Informatics will be greatly recognized. Write a program which calculates the minimum number of residents who will be donated copies of Rie’s book so that all the residents in JOI Kingdom will get copies of Rie’s book.

## 输入格式

Read the following data from the standard input.

> $N$  
> $X_1$ $E_1$  
> $X_2$ $E_2$  
> $\vdots$  
> $X_N$ $E_N$

## 输出格式

Write one line to the standard output. The output should contain the minimum number of residents who will be donated copies of Rie’s book.

## 样例

### 样例输入1
```4
4 2
2 3
3 4
6 5
```

### 样例输出1
```2
```

### 样例输入2
```3
7 10
10 10
7 10
```

### 样例输出2
```2
```

### 样例输入3
```10
31447678 204745778
430226982 292647686
327782937 367372305
843320852 822224390
687565054 738216211
970840050 766211141
563662348 742939240
103739645 854320982
294864525 601612333
375952316 469655019
```

### 样例输出3
```5
```

## 提示

## Samples

### Sample 1

For example, if Rie donates copies of the book in the following way, all the residents in JOI Kingdom will get copies of Rie’s book.

- Rie donates a copy of the book to Resident 3.
  - Since $|X_3 - X_1| = 1$ and $E_3 - E_1 = 2$, Resident 1 will buy a copy of Rie’s book and get it.
  - Since $|X_3 - X_2| = 1$ and $E_3 - E_2 = 1$, Resident 2 will buy a copy of Rie’s book and get it.
  - Since $|X_3 - X_4| = 3$ and $E_3 - E_4 = -1$, Resident 4 will not buy a copy of Rie’s book.
  Therefore, Residents 1, 2, 3 will get copies of Rie’s book.
- Rie donates a copy of the book to Resident 4. Since all the residents except Resident 4 already got copies of Rie’s book, all the residents in JOI Kingdom finally get copies of Rie’s book.

Since it is impossible to donate copies of the book to less than two residents so that all the residents in JOI Kingdom will get copies of Rie’s book, output 2.

This sample input satisfies the constraints of Subtasks 2, 3, 4.

### Sample 2

This sample input satisfies the constraints of all the subtasks.

### Sample 3

This sample input satisfies the constraints of Subtasks 2, 3, 4.

## Constraints

- $1\le N\le 5\times 10^5$.
- $1\le X_i\le 10^9$ ($1\le i\le N$).
- $1\le E_i\le 10^9$ ($1\le i\le N$).
- Given values are all integers.

## Subtasks

1. (10 points) $E_1=E_2=\cdots=E_N$.
2. (23 points) $N\le 16$.
3. (36 points) $N\le 10^3$.
4. (31 points) No additional constraints.

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
