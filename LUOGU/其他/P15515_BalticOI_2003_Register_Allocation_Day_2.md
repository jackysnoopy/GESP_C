# [BalticOI 2003] Register Allocation (Day 2)

## 题目描述

Modern computer processors have a limited number of registers --- general purpose storage locations that are substantially faster than the main memory. The operations that perform computations (e.g. addition, multiplication, etc.) expect their arguments in the registers and return the result in a register.

In this task we consider the problem of *register allocation* for expression evaluation. Inside a compiler, an expression is represented as a tree. Leaf nodes of the tree correspond to values that have to be loaded from the main memory. Intermediate (non-leaf) nodes of the tree correspond to the operations and each of them has as many children as there are arguments to the operation. Obviously, the values of all arguments must be available before an operation can be performed.

Because there is only a limited number of registers, the compiler has to decide which of the intermediate results to keep in the registers (these are available immediately when they are needed) and which ones to store into the main memory (these must be loaded back when they are needed). It may also be useful to change the order of evaluation of the arguments for an operation (this is why most high-level languages do not guarantee any particular order).

Your task is to write a program that, given an expression tree, finds the register allocation plan and evaluation order with the minimal total cost.

## 样例

--- Sample 1 ---
Input:
2
3 2
2
10
2
15
0
0
2
5
0
0
Output:
47
2 0
5 1
1 1

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
