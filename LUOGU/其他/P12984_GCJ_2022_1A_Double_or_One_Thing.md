# [GCJ 2022 #1A] Double or One Thing

## 题目描述

You are given a string of uppercase English letters. You can highlight any number of the letters (possibly all or none of them). The highlighted letters do not need to be consecutive. Then, a new string is produced by processing the letters from left to right: non-highlighted letters are appended once to the new string, while highlighted letters are appended twice.

![](https://cdn.luogu.com.cn/upload/image_hosting/q5ybwo42.png)

For example, if the initial string is HELLOWORLD, you could highlight the H, the first and last Ls and the last o to obtain

HELLOWORLD $\Rightarrow$ HHELLLOWOORLLD. Similarly, if you highlight nothing, you obtain HELLOWORLD, and if you highlight all of the letters, you obtain HHEELLLLOOWWOORRLLDD. Notice how each occurrence of the same letter can be highlighted independently.

Given a string, there are multiple strings that can be obtained as a result of this process, depending on the highlighting choices. Among all of those strings, output the one that appears first in alphabetical (also known as lexicographical) order.

Note: A string $s$ appears before a different string $t$ in alphabetical order if $s$ is a prefix of $t$ or if at the first place $s$ and $t$ differ, the letter in $s$ is earlier in the alphabet than the letter in $t$. For example, these strings are in alphabetical order: CODE, HELLO, HI, HIM, HOME, JAM.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case is described in a single line containing a single string $\mathbf{S}$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the string that comes first alphabetically from the set of strings that can be produced from $\mathbf{S}$ by the process described above.

## 样例

### 样例输入1
```3
PEEL
AAAAAAAAAA
CODEJAMDAY
```

### 样例输出1
```Case #1: PEEEEL
Case #2: AAAAAAAAAA
Case #3: CCODDEEJAAMDAAY
```

## 提示

**Sample Explanation**

In Sample Case #1, these are all the strings that can be obtained, in alphabetical order: PEEEEL, PEEEELL, PEEEL, PEEELL, PEEL, PEELL, PPEEEEL, PPEEEELL, PPEEEL, PPEEELL, PPEEL, and PPEELL.

In Sample Case #2, every string that can be obtained contains only As. The shortest of those is alphabetically first, because it is a prefix of all others.

In Sample Case #3, there are 1024 possible strings which can be generated from CODEJAMDAY out of which CCODDEEJAAMDAAY is the lexicographically smallest one.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- Each character of $\mathbf{S}$ is an uppercase letter from the English alphabet.

**Test Set 1 (10 Pts, Visible Verdict)**

- $1 \leq$ the length of $\mathbf{S} \leq 10$.

**Test Set 2 (15 Pts, Hidden Verdict)**

- $1 \leq$ the length of $\mathbf{S} \leq 100$.

## 解题思路

### 问题分析

选择性加倍字母，使结果字典序最小。

### 核心思路

当s[i] <= s[i+1]时不加倍（更短=更小），否则加倍。最后字符只加一次。

### 算法流程

1. 遍历字符串，比较相邻字符
2. s[i] <= s[i+1]时只加一次，否则加倍
3. 最后字符只加一次

### 复杂度分析

O(n)时间，O(n)空间。
