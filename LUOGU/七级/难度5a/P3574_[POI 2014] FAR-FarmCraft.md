# P3574 [POI 2014] FAR-FarmCraft

## 题目描述

In a village called Byteville, there are $n$ houses connected with $n-1$ roads.

For each pair of houses, there is a unique way to get from one to another.

The houses are numbered from 1 to $n$.

The house no. 1 belongs to the village administrator Byteasar.

As part of enabling modern technologies for rural areas framework, $n$ computers have been delivered to Byteasar's house.

Every house is to be supplied with a computer, and it is Byteasar's task to distribute them.

The travel time along each road linking two houses is exactly 1 minute.

Help Byteasar in determining a delivery order that allows all Byteville's citizens (including Byteasar) to start playing together as soon as possible.

## 输入格式

The first line of the standard input contains a single integer $n$ ($2\le n\le 500\ 000$) that gives the number of houses in Byteville.

The second line contains $n$ integers $c_1,c_2,\cdots,c_n$ ($1\le c_i\le 10^9$), separated by single spaces; $c_i$ is the installation time for the dwellers of house no. i.

The next $n-1$ lines specify the roads linking the houses.

## 输出格式

The first and only line of the standard output should contain a single integer: the (minimum) number of minutes after which all citizens will be able to play FarmCraft together.

## 样例

### 样例1
**输入：**
```
6
1 8 9 6 3 2
1 3
2 3
3 4
4 5
4 6
```

**输出：**
```
11
```

## 解题思路

这是一道树形DP题目。

**算法**：
1. 从叶子节点开始向上计算
2. 考虑每个子树的安装时间和遍历时间
3. 使用贪心选择最优的遍历顺序

**时间复杂度**：$O(n \log n)$

## 相关题目

- 树形DP
- 贪心算法
