# [NWRRC 2022] Computer Network

## 题目描述

Cupa is building a connected network using $n$ computers and a single hub.

The computers are numbered from $1$ to $n$. Each computer $i$ has an outgoing wire that can transfer one bit of data to the other end in $d_i$ milliseconds.

The hub has $k$ ports into which the computer's wires can be connected, and each computer has a single port.

Cupa requires each computer's wire to be connected to some port~--- either in the hub or in another computer. It should also be possible to send data to the hub from every computer, either directly or via other computers.

The network latency $t_i$ for each computer $i$ is defined as the time it takes to send one bit of data from computer $i$ to the hub. We will assume that it takes no time for intermediate computers to redirect received data to their own outgoing wires.

After the network is built, Cupa will calculate the network latency $t_i$ for each computer $i$. He wants the total network latency over all computers, i.e. $t_1 + t_2 + \ldots + t_n$, to be as small as possible.

Help Cupa to build the network in a way that minimizes the total network latency.

## 输入格式

The first line contains two integers $n$ and $k$ --- the number of computers and the number of ports in the hub ($1 \leq k \leq n \leq 100$).

The second line contains $n$ integers $d_1, d_2, \ldots, d_n$ --- the list of data transfer times through each computer's wire ($1 \leq d_i \leq 100$).

## 输出格式

Print a single integer --- the minimum possible total network latency.

## 样例

### 样例输入1
```3 2
20 30 10
```

### 样例输出1
```70
```

### 样例输入2
```5 1
10 10 10 10 10
```

### 样例输出2
```150
```

### 样例输入3
```5 2
10 10 10 10 10
```

### 样例输出3
```90
```

### 样例输入4
```6 3
5 6 2 3 1 4
```

### 样例输出4
```27
```

## 提示

In the first example test, Cupa should connect computers $2$ and $3$ to the hub, and connect computer $1$ to computer $3$. In this case, $t_1 = 20 + 10 = 30$, $t_2 = 30$, and $t_3 = 10$. The answer is $t_1 + t_2 + t_3 = 70$.

In the second example test, the computers should be connected in a chain leading to the hub in arbitrary order. The total network latency is $10 + 20 + 30 + 40 + 50 = 150$.

## 解题思路

### 问题分析

网络延迟最小化，k个端口连接n台电脑。

### 核心思路

贪心：k台直连Hub，其余链式连接，小延迟的靠近Hub。

### 算法流程

1. 排序延迟值
2. 最小的k台直连Hub
3. 其余轮询分配到k条链，延迟累加

### 复杂度分析

O(n log n)时间，O(n)空间。
