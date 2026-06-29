# P3457 [POI 2007] POW-The Flood

## 题目描述

Byteburg, the capital of Byteotia, is a picturesque city situated in a valley in the midst of mountains. Unfortunately, recent heavy rainfall has caused a flood - all the Byteburg is now completely under water.

The king has asked you to determine the minimum number of pumps sufficing to drain the city.

You are provided with a map of the city and the valley it is situated in. The map is in the shape of a $m\times n$ rectangle, divided into unitary squares. For each such square the map tells its height above sea level and whether it is a part of Byteburg or not.

## 输入格式

In the first line of the standard input there are two integers $m$ and $n$, separated by a single space, $1 \le n, m \le 1\ 000$. The following $m$ lines contain the description of the map.

## 输出格式

Your programme should write out one integer to the standard output - the minimum number of pumps needed to drain Byteburg.

## 样例

### 样例1
**输入：**
```
6 9
-2 -2 -1 -1 -2 -2 -2 -12 -3
-2 1 -1 2 -8 -12 2 -12 -12
-5 3 1 1 -12 4 -6 2 -2
-5 -2 -2 2 -12 -3 4 -3 -1
-5 -6 -2 2 -12 5 6 2 -1
-4 -8 -8 -10 -12 -8 -6 -6 -4
```

**输出：**
```
2
```

## 解题思路

这是一道BFS/洪水填充题目。

**算法**：
1. 从每个未访问的城市区域开始BFS
2. 只能流向高度不高于当前高度的格子
3. 统计需要的泵数量

**时间复杂度**：$O(m \times n)$

## 相关题目

- BFS
- 洪水填充
