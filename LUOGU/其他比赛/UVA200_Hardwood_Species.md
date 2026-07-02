# UVA200 - Hardwood Species (硬木种类)

## 题目描述

Hardwoods are the type of tree that has leaves that fall off.

You are given a list of hardwood species and their lengths. Your task is to compute the percentage of each species in the forest.

## 输入格式

The input consists of a list of hardwood species, one per line. The list is terminated by end-of-file.

## 输出格式

For each species, output the name and the percentage (accurate to 4 decimal places) of that species in the forest, one per line, in alphabetical order.

## 样例

输入：
```
Red Alder
Ash
Aspen
Basswood
Ash
Beech
Black Walnut
Cherry
Oak
Oak
Maple
Maple
Ash
```

输出：
```
Ash 38.4615
Aspen 7.6923
Basswood 7.6923
Beech 7.6923
Black Walnut 7.6923
Cherry 7.6923
Maple 15.3846
Oak 15.3846
Red Alder 7.6923
```

## 解题思路

### 问题分析
统计输入中每种硬木物种出现的次数，并计算每种物种占总数的百分比。

### 核心思路
1. 使用 `map<string, int>` 统计每种物种出现的次数
2. 同时维护总树数
3. 最后按字典序输出每种物种的名称和百分比

### 算法流程
1. 逐行读入物种名称，累加计数和总数
2. 遍历 map，输出名称和 `count / total * 100`，保留4位小数

### 复杂度分析
- 时间复杂度：O(N log M)，N为总树数，M为物种数
- 空间复杂度：O(M)

## 参考代码

见 `UVA200_Hardwood_Species.cpp`
