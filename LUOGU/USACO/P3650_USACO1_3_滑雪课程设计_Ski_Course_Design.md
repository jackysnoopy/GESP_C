# [USACO1.3] 滑雪课程设计 Ski Course Design

## 题目描述

Farmer John has $N$ hills on his farm ($1 \le N \le 1000$), each with an integer elevation in the range $0..100$. In the winter, since there is abundant snow on these hills, Farmer John routinely operates a ski training camp.

Unfortunately, Farmer John has just found out about a new tax that will be assessed next year on farms used as ski training camps. Upon careful reading of the law, however, he discovers that the official definition of a ski camp requires the difference between the highest and lowest hill on his property to be strictly larger than $17$. Therefore, if he shortens his tallest hills and adds mass to increase the height of his shorter hills, Farmer John can avoid paying the tax as long as the new difference between the highest and lowest hill is at most $17$.

If it costs $x^2$ units of money to change the height of a hill by $x$ units, what is the minimum amount of money Farmer John will need to pay? Farmer John can change the height of a hill only once, so the total cost for each hill is the square of the difference between its original and final height. Farmer John is only willing to change the height of each hill by an integer amount.

## 输入格式

- Line 1: The integer $N$.
- Lines 2..$N+1$: Each line contains the elevation of a single hill.

## 输出格式

- Line 1: The minimum amount Farmer John needs to pay to modify the elevations of his hills so the difference between largest and smallest is at most $17$ units.

## 样例

### 样例输入1
```5
20
4
1
24
21
```

### 样例输出1
```18
```

## 提示

## Input Details

Farmer John's farm has $5$ hills, with elevations $1$, $4$, $20$, $21$, and $24$.

## Output Details

Farmer John keeps the hills of heights $4$, $20$, and $21$ as they are. He adds mass to the hill of height $1$, bringing it to height $4$ (cost = $3^2 = 9$). He shortens the hill of height $24$ to height $21$, also at a cost of $3^2 = 9$.

USACO Training Section 1.3

## 解题思路

### 问题分析
N个山丘，高度范围0-100。需要让最高和最低的差不超过17，改变高度h需花费h^2。

### 核心思路
枚举最终最低高度lo（0到100），则最高为lo+17。所有低于lo的提升到lo，高于lo+17的降到lo+17。取最小花费。

### 算法流程
1. 读入所有高度
2. 枚举lo从0到100
3. 对每个lo，计算所有山丘调整到[lo, lo+17]的花费
4. 取最小值

### 复杂度分析
时间O(100N)，空间O(N)。N≤1000，非常高效。
