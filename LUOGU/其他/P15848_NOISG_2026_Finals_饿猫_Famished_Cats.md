# [NOISG 2026 Finals] 饿猫 / Famished Cats

## 题目描述

After successfully preventing the extinction of cats during the annual National Cat Day (NCD) celebration, Ket the cat has now received hunger complaints from the kingdom of cannibalistic cats. Hence, Ket has been tasked with delivering food to prevent them from resorting to cannibalism again.

This cat kingdom can be modelled as a very long road that runs from west to east. There is a food bank at the west end of the road. There are $n$ cat houses to the east of the food bank, numbered from 1 to $n$. It is guaranteed that $n$ is **even**. The first house is $d[1]$ kilometres east of the food bank. For $i \geq 2$, the $i$-th house is $d[i]$ kilometres east of the $(i - 1)$-th house.

Ket will drive a delivery truck to deliver food to the houses. The truck starts from the food bank and initially has $x$ units of fuel. 1 unit of fuel allows Ket to drive his truck 1 kilometre along the road.

The $i$-th house has $f[i]$ units of fuel for the truck to use. The truck has infinite fuel storage and stops only when it runs out of fuel. The truck does not need to return to the food bank after leaving.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/20nfiijs.png)
:::

In addition, Ket has a magic wand. In one wave of his wand, he can **swap** the amount of fuel stored in the $i$-th and $(n - i + 1)$-th cats’ houses. This swap can only take place if the fuels in both houses have not been used yet. Help Ket find the index of the farthest house $D$ he can reach, using any number of swaps. Also, help Ket find the minimum number of swaps $S$ required to reach house $D$.

You may refer to Sample Test Case 1 for a more detailed explanation.

## 样例

--- Sample 1 ---
Input:
6 1
1 1 3 1 1 6
1 1 1 4 3 2
Output:
5 1
--- Sample 2 ---
Input:
6 5
3 8 3 1 4 1
2 7 1 6 2 7
Output:
6 1
--- Sample 3 ---
Input:
6 2
2 24 25 40 5 11
4 12 14 16 20 30
Output:
3 2
--- Sample 4 ---
Input:
6 10
3 6 3 7 8 6
4 3 1 7 1 6
Output:
5 1

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
