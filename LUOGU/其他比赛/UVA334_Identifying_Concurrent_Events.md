# UVA334 - Identifying Concurrent Events

## 题目描述

给定一组事件和事件之间的先后关系（偏序关系），找出所有"并发"的事件对。两个事件 $A$ 和 $B$ 是并发的，当且仅当 $A$ 既不在 $B$ 之前，$B$ 也不在 $A$ 之前（即两者之间没有因果关系）。

## 输入格式

多组测试数据。每组第一行两个整数 $n$（事件数）和 $m$（关系数），接下来 $n$ 行事件名，$m$ 行每行两个事件名（表示前者必须在后者之前发生）。$n = m = 0$ 时结束。

## 输出格式

```
City being analyzed: X
Y concurrent events:
事件A,事件B are concurrent.
...
```

## 样例输入

```
4 3
A
B
C
D
A B
A C
B D
4 4
A
B
C
D
A B
B C
C D
D A
0 0
```

## 样例输出

```
City being analyzed: 1
2 concurrent events:
C,D are concurrent.
B,C are concurrent.

City being analyzed: 2
0 concurrent events:

```

## 解题思路

1. 将事件名映射为编号
2. 用邻接矩阵建立有向图
3. Floyd-Warshall 求传递闭包：$reach[i][j] = true$ 表示 $i$ 在 $j$ 之前
4. 两个事件 $i$、$j$ 是并发的当且仅当 $reach[i][j] = false$ 且 $reach[j][i] = false$
5. 枚举所有事件对，输出并发事件对

## 时间复杂度

$O(n^3)$（Floyd-Warshall）

## 空间复杂度

$O(n^2)$
