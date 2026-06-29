# P3424 [POI 2005] SUM-Fibonacci Sums

## 题目描述

Fibonacci numbers are an integer sequence defined in the following way: $Fib_0=1$, $Fib_1=1$, $Fib_i=Fib_{i-1}+Fib_{i-2}$ (for $i\ge 2$).

The great computer scientist Byteazar is constructing an unusual computer, in which numbers are represented in Fibonacci system. A bit string $(b_1,b_2,\cdots,b_n)$ denotes the number $b_1\cdot Fib_1+b_2\cdot Fib_2+\cdots+b_n\cdot Fib_n$.

Byteazar has limited himself to only using representations satisfying the following conditions:
1. if $n>1$, then $b_n=1$, i.e. the representation of a number does not contain leading zeros.
2. if $b_i=1$, then $b_{i+1}=0$ (for $i=1,\cdots,n-1$), i.e. the representation of a number does not contain two (or more) consecutive ones.

## 输入格式

The input contains the Fibonacci representations (satisfying the aforementioned conditions) of two positive integers $x$ and $y$ - one in the first, the other in the second line.

## 输出格式

In the first and only line of the output your programme should write the Fibonacci representation (satisfying the aforementioned conditions) of the sum $x+y$.

## 样例

### 样例1
**输入：**
```
4 0 1 0 1
5 0 1 0 0 1
```

**输出：**
```
6 1 0 1 0 0 1
```

## 解题思路

这是一道Fibonacci进制加法问题。

**算法**：
1. 将两个Fibonacci表示相加
2. 处理进位和连续的1
3. 转换为标准形式

**时间复杂度**：$O(n)$

## 相关题目

- Fibonacci数列
- 进制转换
