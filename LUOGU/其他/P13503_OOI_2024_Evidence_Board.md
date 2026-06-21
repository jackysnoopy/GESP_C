# [OOI 2024] Evidence Board

## 题目描述

Volodya dreams of becoming a detective. Therefore, Volodya often reads books that tell incredible stories of solving crimes. Studying the next case, Volodya came across interesting details of the investigation.

There were a total of $n$ suspected persons in the case. The evidence board contains all $n$ persons. Initially, there were no connections between them.

During the investigation, new connections between suspected persons emerged one after another. Each connection linked two persons that previously had no connection with each other, even indirectly through several other persons.

Let's consider what happened when a connection between persons $A$ and $B$ emerged. In addition to the names of the persons, each connection had three parameters: $c_A$ --- the strength of the evidence against $A$, $c_B$ --- the strength of the evidence against $B$, and $w_{AB}$ --- the total strength of the evidence of connection. For natural reasons, the strength of the evidence of connection could not exceed the sum of strengths of the evidence against $A$ and $B$. That means that for each connection, it was $\textbf{necessarily}$ that $w_{AB} \leq c_A + c_B$. Upon receiving such connection, the detectives drew a line on the board between the images of persons $A$ and $B$, assigning the $w_{AB}$ to this line. Also, a sticker with the number $c_A$ was placed on the image of person $A$, and a sticker with the number $c_B$ was placed on $B$. If there were already other stickers on the image, the new sticker was placed on top of the old ones.

The case was solved exactly at the moment when all the suspected persons were linked through $n-1$ connections. After solving the crime, the board was placed in the museum in its original form.

Inspired by this approach, Volodya visited that museum and studied the evidence board in detail. Volodya noticed that the image of person $v$ contained stickers with numbers $c_{v,1}, \ldots, c_{v,deg_v}$ numbered $\textbf{from top to bottom}$. Here, $deg_v$ denotes the number of connections associated with person $v$. Also, Volodya remembered that the $i$-th connection was between persons $a_i$ and $b_i$ and had evidence strength $w_i$. Unfortunately the connections were arbitrarily numbered, and their numbers did not necessarily correspond to the order in which they appeared during the investigation.

Due to the confusion with the numbers of connections, the information on the board did not help to restore the process of the investigation. Now Volodya needs to restore any possible chronological order in which the connections could have emerged for the detectives. This task is too difficult for him, so he asks your help. It is also possible that the museum falsified information, and a suitable order does not exist.

## 样例

--- Sample 1 ---
Input:
5 0
1 2 3
1 3 1
3 4 12
3 5 6
0 4
2
6 1 3
8
3
Output:
Yes
1 4 2 3
--- Sample 2 ---
Input:
7 0
1 2 4
2 3 4
3 4 4
4 5 4
5 6 4
6 7 4
2
1 2
2 3
1 2
3 2
1 2
179
Output:
Yes
5 1 2 3 6 4
--- Sample 3 ---
Input:
4 0
1 2 7
1 3 6
1 4 5
3 2 1
5
4
3
Output:
No

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
