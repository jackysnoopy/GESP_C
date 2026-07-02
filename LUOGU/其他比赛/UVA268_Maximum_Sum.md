# UVA268 - Maximum Sum (最大和)

## 题目描述

给定一个 $N \times N$ 的整数矩阵（$1 \le N \le 100$），求其中和最大的连续子矩阵（矩形区域）的和。

矩阵中的整数范围为 $-127$ 到 $127$。

## 输入格式

多组测试数据。每组第一行为整数 $N$，若 $N = 0$ 则结束输入。接下来 $N$ 行，每行 $N$ 个整数，表示矩阵的元素。

## 输出格式

对每组输入，输出一行，包含一个整数，表示最大子矩阵的和。相邻两组输出之间用一个空行分隔。

## 样例输入

```
4
0 -2 -7  0
 9  2 -6 -2
-4  1 -4  1
-1  8  0 -2
0
```

## 样例输出

```
15
```

## 解题思路

### 算法：二维最大子数组（Kadane 算法扩展）

核心思想是将二维问题降为一维问题：

1. **枚举上下边界**：对于每一对行 $(top, bottom)$，将矩阵压缩为一维数组 `colSum`，其中 `colSum[j]` 表示第 $j$ 列从第 $top$ 行到第 $bottom$ 行的元素之和。

2. **一维 Kadane 算法**：对压缩后的一维数组 `colSum` 应用 Kadane 算法，求出最大连续子数组和。

3. **枚举所有行对**：遍历所有 $(top, bottom)$ 对（$0 \le top \le bottom < N$），取所有结果的最大值。

### 算法步骤

```
for top = 0 to N-1:
    colSum[0..N-1] 初始化为 0
    for bottom = top to N-1:
        colSum[j] += mat[bottom][j]   // 累加第 bottom 行
        对 colSum 运行一维 Kadane，更新全局最大值
```

### 一维 Kadane 算法

```
maxEndingHere = colSum[0]
maxSoFar = colSum[0]
for j = 1 to N-1:
    maxEndingHere = max(colSum[j], maxEndingHere + colSum[j])
    maxSoFar = max(maxSoFar, maxEndingHere)
```

### 时间复杂度

$O(N^3)$：枚举上下界 $O(N^2)$，每次 Kadane 扫描 $O(N)$。

### 空间复杂度

$O(N)$：仅需一维数组 `colSum`。

### 关键点

- 使用 `long long` 避免溢出（$N \le 100$，元素绝对值 $\le 127$，最大子矩阵和不超过 $100 \times 100 \times 127 = 1{,}270{,}000$，不会溢出 `int`，但使用 `long long` 更安全）
- 相邻两组输出之间需空行分隔，注意首组不输出前置空行
- 输入以 $N = 0$ 结束
