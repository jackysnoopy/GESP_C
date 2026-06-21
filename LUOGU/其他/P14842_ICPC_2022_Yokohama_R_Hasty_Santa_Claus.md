# [ICPC 2022 Yokohama R] Hasty Santa Claus

## 题目描述

Hasty Santa Claus has arrived at the town on December 1st. Realizing that it is a little bit too early for Christmas, he plans to leave the presents before (or even after) Christmas while families are out on vacation trips.

Santa knows which families depart and return on which days, but he can visit only a limited number of houses a day. He is stuck with finding which houses are to be visited on which days to distribute the presents to every family. Please help him solving the problem, not only for Santa but also for kids anxiously awaiting for the presents!

## 输入格式

The input consists of a single test case of the following format.

$$
\begin{aligned}
&n \quad k \\
&a_1 \quad b_1 \\
&\vdots \\
&a_n \quad b_n
\end{aligned}
$$

The first line has two positive integers, $n$ and $k$, the number of houses to leave the presents and the maximum number of houses that Santa Claus can visit a day, respectively.

The $i$-th line of the following $n$ lines has two positive integers $a_i$ and $b_i$. They indicate that he can visit the $i$-th house between the $a_i$-th and $b_i$-th days, inclusive.

$n$ and $k$ satisfy $1 \le k \le n \le 1000$. For each $i$, $a_i$ and $b_i$ satisfy $1 \le a_i \le 25 \le b_i \le 31$.

## 输出格式

rint $n$ lines of one integer describing a plan for Santa to complete his task. The integer on the $i$-th line means the date on which Santa should visit the $i$-th house.

At least one solution is guaranteed to exist. If there are two or more solutions, any of them is accepted.

## 样例

### 样例输入1
```5 1
23 25
23 27
24 25
25 25
25 26
```

### 样例输出1
```23
27
24
25
26
```

### 样例输入2
```7 2
1 31
1 31
1 31
1 31
1 31
1 31
1 31
```

### 样例输出2
```1
1
2
2
3
3
4
```

### 样例输入3
```6 2
24 25
24 25
24 25
25 26
25 26
25 26
```

### 样例输出3
```24
25
24
26
25
26
```

## 提示

The first sample is depicted in the figure below. Santa can leave the presents during the periods shown as horizontal lines with short vertical markers at both ends. For the House 4, Santa can visit only on a specific day. The triangles show the days on which Santa should visit each house.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/a554msx0.png)

Figure A.1. Sample 1
:::

## 解题思路

### 问题分析

圣诞老人送礼物，最多访问房子数。

### 核心思路

贪心：按返回日期排序，选择最早可访问的房子。

### 算法流程

1. 按返回日期排序
2. 贪心选择不冲突的房子

### 复杂度分析

O(n log n)时间，O(n)空间。
