# [NOISG 2026 Prelim] Hungry Cats

## 题目描述

In the kingdom of cannibalistic cats, Ket the cat has just been informed that National Cat Day (NCD) will be held tomorrow. As the appointed software engineer, he is tasked with developing a system to report on the cannibalism situation.

There are $n$ cats joining the NCD celebration, numbered from 1 to $n$. The $i$-th cat has a happiness level of $h[i]$. At any point in time, a cat may eat a **strictly** less happy cat. After this happens, the happier cat’s happiness level **increases by $1$** and it is **no longer able to eat any other cats**. In addition, the less happy cat vanishes.

Ket is tasked with determining whether it is possible for only one cat to be left at the end of the celebration. This means that all other cats were eaten.

## 输入格式

Your program must read from standard input.

The first line of input contains an integer $n$.

The second line of input contains $n$ space-separated integers $h[1], h[2], \ldots, h[n]$.

## 输出格式

Your program must print to standard output.

Output **YES** if it is possible for only one cat to be left after the celebration, or **NO** otherwise.

## 样例

### 样例输入1
```2
3141 59
```

### 样例输出1
```YES
```

### 样例输入2
```3
31 41 59
```

### 样例输出2
```YES
```

### 样例输入3
```5
10 0 24 25 10
```

### 样例输出3
```NO
```

### 样例输入4
```6
2 25 11 5 20 26
```

### 样例输出4
```NO
```

## 提示

### Sample Test Case 2 Explanation

There are $n = 3$ cats with hunger levels $31$, $41$, and $59$. It is possible for one cat to be left after the celebration if the second cat eats the first cat and subsequently gets eaten by the third cat.

### Sample Test Case 3 Explanation

It is impossible for the cats to eat each other in a way that leaves one cat remaining at the end of the celebration.


### Subtasks

For all test cases, the input will satisfy the following bounds:

- $2 \le n \le 200\,000$
- $0 \le h[i] \le 10^9$ for all $1 \le i \le n$

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Score | Additional Constraints                      |
|:-------:|:-----:|:-------------------------------------------:|
| 0       | 0     | Sample test cases                           |
| 1       | 8     | $n = 2$                                     |
| 2       | 10    | $n \le 3$                                   |
| 3       | 6     | $h[1] = h[n]$                               |
| 4       | 18    | $n \le 1000$                                |
| 5       | 28    | $h$ is non-decreasing ($h[i] \le h[i+1]$ for all $1 \le i \le n-1$) |
| 6       | 30    | No additional constraints                   |

## 解题思路

### 问题分析

n 只猫，happiness h[i]，严格快乐的猫可以吃严格不快乐的猫（+1 且不能再吃），问能否只剩一只。

### 核心思路

排序后，最大的猫依次吃其他猫。第 k 只被吃的猫 happiness 为 a[k]，需要 a[n-1]+k > a[k]。若所有条件满足则 YES。

### 算法流程

1. 排序
2. 检查对所有 k < n-1：h[n-1]+k > h[k]
3. 输出 YES/NO

### 复杂度分析

时间 O(n log n)，空间 O(n)
