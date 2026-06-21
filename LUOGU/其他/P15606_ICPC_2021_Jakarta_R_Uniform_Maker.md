# [ICPC 2021 Jakarta R] Uniform Maker

## 题目描述

The International Costumes and Props Company (ICPC) received an order from a client to produce $N$ pennants each containing the same word. However, due to some miscommunication between the account manager and the client, not all the produced pennants have the same word although all of them have a word of the same length. Reproducing those pennants is very costly as the ICPC only uses a certain type of rare fabric in their production.

Fortunately, the client didn't specify the word that they want to be in the pennants. In fact, the client will be satisfied if and only if all the pennants have the same word.

The ICPC has a special technique to change one character in a word into some other character. It is expensive, albeit not as expensive as reproducing a new pennant. Therefore, the ICPC has to minimize the number of times they have to use such a technique. Your task in this problem is to help the ICPC to determine the minimum total number of characters that need to be changed so that the client will be satisfied.

For example, let there be $N = 6$ pennants with the following words: calf, palm, book, icpc, ball, and room. The total number of characters that need to be changed can be minimized if all the words are changed into balm.

- calf → 2 characters: b**m
- palm → 1 characters: b***
- book → 3 characters: *alm
- icpc → 4 characters: balm
- ball → 1 characters: ***m
- room → 3 characters: bal*

The symbol * represents an unchanged character. There are a total of $14$ characters that need to be changed in this example.

## 输入格式

Input begins with a line containing two integers $N$ $M$ ($2 \leq N \leq 100$; $1 \leq M \leq 100$) representing the number of pennants and the length of each word in the pennant, respectively. The next $N$ line each contains a string $S_i$ ($|S_i| = M$) representing the word on the $i^{th}$ pennant. Each string only contains lowercase alphabetical characters.

## 输出格式

Output contains an integer in a line representing the minimum total number of characters that need to be changed so that the client will be satisfied.

## 样例

### 样例输入1
```6 4
calf
palm
book
icpc
ball
room
```

### 样例输出1
```14
```

### 样例输入2
```3 11
goodluckfor
icpcjakarta
contestants
```

### 样例输出2
```19
```

### 样例输入3
```5 14
helpiamtrapped
inanincfactory
forthreemonths
withoutfoodand
drinkandshower
```

### 样例输出3
```49
```

## 提示



## 解题思路

### 问题分析

N 个单词每个 M 个字符，每列选最优字符，使总改动最小。

### 核心思路

对每列统计各字符出现频率，选频率最高的字符保留，其余改为该字符。

### 算法流程

1. 对每列统计频率
2. 改动数 = N - max(频率)
3. 累加所有列

### 复杂度分析

时间 O(NM)，空间 O(M)
