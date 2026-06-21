# [ICPC 2021 Seoul R] Logistical Warehouse 2

## 题目描述

KOPANG is one of largest online vendors in Korea and introduced so called "early-morning delivery" for the first time. To cope with the growing demand, KOPANG plans to build new logistical warehouses. The locations of logistical warehouses must be within a certain distance from customers to keep the delivery time guaranteed by KOPANG to the customers.

The logistics network is modelled as a connected tree $T$. Each node of $T$ represents a region such as a city or a province in Korea, and each edge of $T$ represents a transportation road connecting two regions. KOPANG wants to select one or more nodes of $T$ satisfying the **distance restriction** for the logistical warehouses. Before the selection, KOPANG first fixed a distance parameter $K$ through sufficient research. KOPANG now wants to select the minimum number of nodes satisfying the distance restriction that the distance from every node of $T$ to its closest selected node (warehouse) is at most $K$. The distance of two nodes $u$ and $v$ is the number of edges of the (unique) path in $T$ that connects $u$ and $v$. Note that the distance is defined as zero if $u = v$.

For example, Figure G.1 below shows a tree $T$ with nine nodes and eight edges. For $K = 1$, if three warehouses are located at nodes 2, 5, and 8, marked with red circles as in Figure G.1 (a), then the distance of every node of $T$ to the closest warehouse is at most one. Two warehouses are not enough to satisfy the distance restriction, so three warehouses are the minimum. For $K = 2$, three warehouses are still required; warehouses at nodes 2, 5, and 8 for $K = 1$ are the ones for $K = 2$. Of course, the locations of the minimum number of warehouses are not unique; three warehouses at nodes 4, 7, and 1 as in Figure G.1 (b) also satisfy the distance restriction for $K = 2$.

Given a connected tree $T$ and a positive integer $K$, write a program to select the minimum number of nodes (warehouses) of $T$ satisfying the distance restriction, that is, the distance of every node of $T$ to its closest warehouse is at most $K$.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/j51fgnld.png)

Figure G.1 The nodes marked with red circles are the ones selected for warehouses.
:::

## 样例

--- Sample 1 ---
Input:
9 1
2 1
7 3
3 4
4 5
6 5
7 8
3 2
8 9
Output:
3
--- Sample 2 ---
Input:
9 2
2 1
7 3
3 4
4 5
6 5
7 8
3 2
8 9
Output:
3
--- Sample 3 ---
Input:
9 8
2 1
7 3
3 4
4 5
6 5
7 8
3 2
8 9
Output:
1

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
