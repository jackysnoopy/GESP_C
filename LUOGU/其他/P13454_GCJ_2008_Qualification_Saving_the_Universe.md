# [GCJ 2008 Qualification] Saving the Universe

## 题目描述

The urban legend goes that if you go to the Google homepage and search for "Google", the universe will implode. We have a secret to share... It is true! Please don't try it, or tell anyone. All right, maybe not. We are just kidding.

The same is not true for a universe far far away. In that universe, if you search on any search engine for that search engine's name, the universe does implode!

To combat this, people came up with an interesting solution. All queries are pooled together. They are passed to a central system that decides which query goes to which search engine. The central system sends a series of queries to one search engine, and can switch to another at any time. Queries must be processed in the order they're received. The central system must never send a query to a search engine whose name matches the query. In order to reduce costs, the number of switches should be minimized.

Your task is to tell us how many times the central system will have to switch between search engines, assuming that we program it optimally.

## 输入格式

The first line of the input file contains the number of cases, $N$. $N$ test cases follow.

Each case starts with the number $S$ -- the number of search engines. The next $S$ lines each contain the name of a search engine. Each search engine name is no more than one hundred characters long and contains only uppercase letters, lowercase letters, spaces, and numbers. There will not be two search engines with the same name.

The following line contains a number $Q$ -- the number of incoming queries. The next $Q$ lines will each contain a query. Each query will be the name of a search engine in the case.

## 输出格式

For each input case, you should output:

Case #$X$: $Y$

where $X$ is the number of the test case and $Y$ is the number of search engine switches. Do not count the initial choice of a search engine as a switch.

## 样例

### 样例输入1
```2
5
Yeehaw
NSM
Dont Ask
B9
Googol
10
Yeehaw
Yeehaw
Googol
B9
Googol
NSM
B9
NSM
Dont Ask
Googol
5
Yeehaw
NSM
Dont Ask
B9
Googol
7
Googol
Dont Ask
NSM
NSM
Yeehaw
Yeehaw
Googol
```

### 样例输出1
```Case #1: 1
Case #2: 0
```

## 提示

**Sample Explanation**

In the first case, one possible solution is to start by using Dont Ask, and switch to NSM after query number 8.

For the second case, you can use B9, and not need to make any switches.

**Limits**

- $0 < N \leq 20$

**Small dataset (5 Pts, Test set 1 - Visible)**

- $2 \leq S \leq 10$
- $0 \leq Q \leq 100$

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $2 \leq S \leq 100$
- $0 \leq Q \leq 1000$

## 解题思路

### 问题分析

搜索引擎切换问题，最小化切换次数。

### 核心思路

贪心：当当前引擎无法处理查询时切换到能处理所有后续查询的引擎。

### 算法流程

1. 维护当前引擎
2. 如果查询匹配当前引擎，切换
3. 选择能处理最多后续查询的引擎

### 复杂度分析

O(S×Q)时间，O(S+Q)空间。
