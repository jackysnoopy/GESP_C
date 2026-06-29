# P3099 [USACO14JAN] Cow Curling G

## 题目描述

Cow curling is a popular cold-weather sport played in the Moolympics.

Like regular curling, the sport involves two teams, each of which slides N heavy stones across a sheet of ice. At the end of the game, there are 2N stones on the ice, each located at a distinct 2D point.

A stone is said to be "captured" if it is contained inside a triangle whose corners are stones owned by the opponent (a stone on the boundary of such a triangle also counts as being captured). The score for a team is the number of opponent stones that are captured.

## 输入格式

Line 1: The integer N.

Lines 2..1+N: Each line contains 2 integers specifying the x and y coordinates of a stone for team A.

Lines 2+N..1+2N: Each line contains 2 integers specifying the x and y coordinates of a stone for team B.

## 输出格式

Line 1: Two space-separated integers, giving the scores for teams A and B.

## 样例

### 样例1
**输入：**
```
4 
0 0 
0 2 
2 0 
2 2 
1 1 
1 10 
-10 3 
10 3 
```

**输出：**
```
1 2 
```

## 解题思路

这是一道计算几何题目，涉及凸包。

**算法**：
1. 分别计算两队的凸包
2. 对于每个对方的点，检查是否在凸包内
3. 统计得分

**时间复杂度**：$O(N \log N)$

## 相关题目

- 凸包
- 计算几何
