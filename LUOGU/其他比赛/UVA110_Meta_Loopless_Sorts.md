# UVA110 - Meta-Loopless Sorts (元无循环排序)

## 题目描述

给定 $n$（$n \leq 8$）个变量名，要求生成一段 Pascal 风格的排序程序。该程序使用嵌套的 if-else 语句来对这 $n$ 个整数变量进行排序，要求：

1. 不使用任何循环（loopless）
2. 输出的 if-else 嵌套结构能够正确排序所有可能的输入排列
3. 输出格式为 Pascal 语言的程序结构

## 输入格式

第一行：测试用例数量 $T$

每个测试用例：
- 第一行：变量个数 $n$
- 第二行：$n$ 个变量名（字符串）

## 输出格式

每个测试用例输出一个完整的 Pascal 排序程序，包含：
- `program` 声明
- `var` 变量声明
- `begin...end` 块，内含嵌套的 if-else 排序逻辑和 `writeln` 输出

## 样例输入

```
2
2
a b
3
a b c
```

## 样例输出

```
program sort(input, output);
var
  a, b : integer;
begin
  writeln(a, b)
if a < b then
  writeln(a, b)
else
  writeln(b, a)
end.

program sort(input, output);
var
  a, b, c : integer;
begin
  writeln(a, b, c)
if a < b then
  if a < c then
    if b < c then
      writeln(a, b, c)
    else
      writeln(a, c, b)
  else
    writeln(c, a, b)
else
  if b < c then
    if a < c then
      writeln(b, a, c)
    else
      writeln(b, c, a)
  else
    writeln(c, b, a)
end.
```

## 解题思路

### 问题分析

本题要求生成一个"无循环排序"程序。本质上是生成一个完整的决策树，覆盖 $n!$ 种排列情况，使用嵌套 if-else 实现。

### 核心思路

采用**插入排序的思想**生成嵌套 if-else 结构：

1. **第一个变量**：无需比较，直接加入有序列表
2. **后续变量**：依次与有序列表中的元素从左到右比较，找到正确的插入位置

对于每个待插入的变量 `var`：
- 比较 `sorted[0] < var`：如果为真，继续比较下一个；如果为假，插入到位置 0
- 比较 `sorted[1] < var`：如果为真，继续比较下一个；如果为假，插入到位置 1
- ...
- 如果 `var` 大于所有元素，插入到末尾

### 算法流程

```
generateCode(depth, sorted):
    if depth == n:
        输出 writeln(sorted)
    else:
        var = vars[depth]
        if depth == 0:
            sorted.push(var)
            generateCode(depth + 1, sorted)
        else:
            for pos in 0..depth:
                输出 "if sorted[pos] < var then" (或 "else if")
                递归处理 TRUE 分支 (pos+1)
                输出 "else"
                sorted.insert(pos, var)
                输出 writeln(sorted)
                sorted.erase(pos)
```

### 复杂度分析

- **时间复杂度**：$O(n! \cdot n)$，需要生成 $n!$ 个叶节点，每个叶节点输出 $O(n)$ 个变量
- **空间复杂度**：$O(n)$，递归深度为 $n$

## 参考代码

见 `UVA110.cpp`
