# [ICPC 2023 Yokohama R] Do It Yourself?

## 题目描述

You are the head of a group of $n$ employees including you in a company. Each employee has an employee ID, which is an integer 1 through $n$, where your ID is 1. Employees are often called by their IDs for short: $\#1$, $\#2$, and so on. Every employee other than you has a unique *immediate boss*, whose ID is smaller than his/hers. A *boss* of an employee is transitively defined as follows.

- If an employee $\#i$ is the immediate boss of an employee $\#j$, then $\#i$ is a boss of $\#j$.
- If $\#i$ is a boss of $\#j$ and $\#j$ is a boss of $\#k$, then $\#i$ is a boss of $\#k$.

Every employee including you is initially assigned exactly one task. That task can be done by him/herself or by any one of his/her bosses. Each employee can do an arbitrary number of tasks, but doing many tasks makes the employee too tired. Formally, each employee $\#i$ has an individual fatigability constant $f_i$, and if $\#i$ does $m$ tasks in total, then the *fatigue level* of $\#i$ will become $f_i \times m^2$.

Your mission is to minimize the sum of fatigue levels of all the $n$ employees.

## 样例

--- Sample 1 ---
Input:
4
1 1 2
1 1 1 1
Output:
4
--- Sample 2 ---
Input:
4
1 1 2
1 10 10 10
Output:
16
--- Sample 3 ---
Input:
4
1 1 2
1 2 4 8
Output:
10

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
