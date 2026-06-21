# [SDCPC 2023] Fast and Fat

## 题目描述

You're participating in a team competition of trail running. There are $n$ members in your team where $v_i$ is the speed of the $i$-th member and $w_i$ is his/her weight.

The competition allows each team member to move alone or carry another team member on their back. When member $i$ carries member $j$, if member $i$'s weight is greater than or equal to member $j$'s weight, member $i$'s speed remains unchanged at $v_i$. However, if member $i$'s weight is less than member $j$'s weight, member $i$'s speed will decrease by the difference of their weight and becomes $v_i - (w_j - w_i)$. If member $i$'s speed will become negative, then member $i$ is not able to carry member $j$. Each member can only carry at most one other member. If a member is being carried, he/she cannot carry another member at the same time.

For all members not being carried, the speed of the slowest member is the speed of the whole team. Find the maximum possible speed of the whole team.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^5$) indicating the number of team members.

For the following $n$ lines, the $i$-th line contains two integers $v_i$ and $w_i$ ($1 \le v_i, w_i \le 10^9$) indicating the speed and weight of the $i$-th member.

It's guaranteed that the sum of $n$ of all test cases will not exceed $10^5$.

## 输出格式

For each test case output one line containing one integer indicating the maximum speed of the whole team.

## 样例

### 样例输入1
```2
5
10 5
1 102
10 100
7 4
9 50
2
1 100
10 1
```

### 样例输出1
```8
1
```

## 提示

The optimal strategy for the sample test case is shown as follows:

- Let member $1$ carry member $4$. As $w_1 > w_4$, member $1$'s speed remains unchanged, which is still $10$.
- Let member $3$ carry member $2$. As $w_3 < w_2$, member $3$'s speed will decrease by $w_2 - w_3 = 2$ and becomes $10 - 2 = 8$.
- Member $5$ shall move alone. His/Her speed is $9$.

So the answer is $8$.

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
