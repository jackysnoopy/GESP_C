# 「Wdcfr-1」Magical Expression

## 题目描述

Nitori is learning postfix expressions. She has a incomplete postfix expression $E$ of length $n$. Being a Youkai, she wants to find its magical property.

Her postfix expression contains the Bitwise Or operator (denoted as `|`), the Bitwise And operator (denoted as `&`), and numbers `0` and `1`. Being incomplete, some operators have not been decided yet and are denoted as `?`. She promised that $E$ **will become a *vaild* postfix expression** after you complete it.

In this problem, the term *substring* is defined as a continuous segment of $E$. **Two substrings are considered different as long as their positions or length differ.**  So `1?0`, `01?0` are all substrings of `01?01?|`  , but `0101` is not.

Nitori found out that a substring of her expression is *magical* if and only if the following conditions are met:

- It is possible to transform it into a *valid* postfix expression after replacing `?` with either `&` or `|` .
- Among these transformations, it is possible to find at least one of them that after applying it, the expression yields $0$,  and at least one of them that after applying it, the expression yields $1$.

Your task is to find out the number of *magical* substrings.

## 输入格式

The first line contains an integer $T$, the number of test cases.

For each test case, input one integer $n$ and an expression $E$ in a single line.

## 输出格式

For each test case, print one integer which is the answer.

## 样例

### 样例输入1
```2
3 01?
7 01?01?|
```

### 样例输出1
```1
3
```

## 提示

### Constraints

$1\le T,n\le 2\times 10^6$. The sum of $n$ of all test cases $\le 2\times 10^6$.

## 解题思路

### 问题分析
后缀表达式，`?` 可替换为 `&` 或 `|`。统计"魔法子串"数量（可合法且可 0 可 1）。

### 核心思路
枚举子串，检查是否可构成合法后缀表达式，且存在使结果为 0 和 1 的替换。

### 算法流程
1. 枚举子串
2. 检查合法性和灵活性

### 复杂度分析
时间 $O(n^2)$，空间 $O(n)$。
