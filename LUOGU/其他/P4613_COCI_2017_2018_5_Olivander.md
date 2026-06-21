# [COCI 2017/2018 #5] Olivander

## 题目描述

Harry Potter has damaged his magic wand in a fight with Lord Voldemort. He has decided to
get a new wand in Olivander's wand shop. On the floor of the shop, he saw ​N wands and ​N
wand boxes. The lengths of the wands are, respectively, $X_1$
,$X_2$
...​$X_n$
, and the box sizes are
$Y_1$
,​$Y_2$
...$Y_n$
. A wand of length ​X can be placed in a box of size ​Y if ​X ≤ ​Y
. Harry wants to know
if he can place all the wands in boxes so that each box contains exactly one wand.
Help him solve this difficult problem.

## 输入格式

The first line of input contains the positive integer ​N
(1 ≤ ​N
≤ 100), the number from the task.
The second line contains ​N
positive integers ​$X_i$
(1 ≤ ​$X_i$
≤ $10^9$​ ), the numbers from the task.
The third line contains ​N
positive integers ​$X_i$
(1 ≤ $X_i$
≤ $10^9$​​ ), the numbers from the task.

## 输出格式

If Harry can place all the wands in boxes, output “DA” (Croatian for yes), otherwise output
“NE” (Croatian for no).

## 样例

### 样例输入1
```3
7 9 5
6 13 10
```

### 样例输出1
```DA
```

### 样例输入2
```4
5 3 3 5
10 2 10 10
```

### 样例输出2
```NE
```

### 样例输入3
```4
5 2 3 2
3 8 3 3
```

### 样例输出3
```DA
```

## 提示

In test cases worth 60% of total points, it will hold ​N
≤ 9.

**Clarification of the first test case:**

Harry can place the wands in boxes. For example, he can place the wand of length 5 in a box of size
6, wand of length 7 in a box of size 13, and wand of length 9 in a box of size 10.

**Clarification of the second test case:**

Harry can’t place the wands in boxes because the box of size 2 can’t fit any of the wands.

## 解题思路

### 问题分析
N根魔杖和N个盒子，魔杖X放入盒子Y需X≤Y。判断是否能一一对应。

### 核心思路
贪心：将魔杖和盒子都排序，逐个检查最小的魔杖能否放入最小的盒子。

### 算法流程
1. 排序魔杖和盒子
2. 对每个i检查w[i]≤b[i]
3. 全部满足输出"DA"，否则"NE"

### 复杂度分析
时间O(N log N)，空间O(N)。
