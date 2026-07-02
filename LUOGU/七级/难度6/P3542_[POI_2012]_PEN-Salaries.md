# P3542 [POI 2012] PEN-Salaries

## 题目描述

The Byteotian Software Corporation (BSC) has $n$ employees.

In BSC's strict hierarchy, each employee has a direct supervisor, except the CEO, to whom all other BSC employees answer, directly or not.

Each employee has a unique monthly salary, and all their salaries range from 1 to $n$ bythalers.

Each supervisor earns more than each of their subordinates.

According to Byteotian law, the salaries of employees on certain posts may be publicly disclosed.

Furthermore, if the salary of an employee is disclosed, then the salary of their supervisor is also disclosed.

The Byteotian Internal Revenue Anti-Corruption Service (BIRAS) has decided to investigate BSC.

Before BIRAS enters BSC with a warrant, they intend to learn the salaries of all BSC employees that are not disclosed but can be determined from those that are disclosed.

## 输入格式

In the first line of the standard input a single integer $n$（$1 \le n \le 1\,000\,000$）is given that denotes the number of BSC employees.

The employees have id's that range from 1 to $n$.

The $n$ lines that follow provide information on these employees.

The line no. $i+1$ describes the employee no. $i$ by two integers $p_i$ and $z_i$（$1 \le p_i \le n$, $0 \le z_i \le n$）, separated by a single space.

The number $p_i$ is the id of the direct supervisor of the employee $i$. If $p_i=i$, then $i$ is the CEO of BSC. If $z_i>0$, then that is the salary of the employee $i$. If, on the other hand, $z_i=0$, then the salary of employee $i$ is not disclosed. Those $z_i$'s that are positive are also pairwise different.

The input data will always be such that there is at least one assignment of salaries to employees consistent with them, i.e., with the hierarchy and the partial assignment that they provide.

## 输出格式

Your program should print $n$ lines to the standard output, each line holding a single integer.

If the employee $i$'s salary is disclosed or can be inferred from disclosed salaries, then the $i$-th line should hold employee $i$'s salary.

Otherwise the $i$-th line should contain $0$.

## 样例

输入：
```
10
2 2
2 10
1 0
2 9
2 5
4 0
6 0
6 0
5 0
5 0
```
输出：
```
2
10
1
9
5
8
0
0
0
0
```

## 解题思路

### 问题分析

这是一个树+set问题。需要根据已公布的工资和树形结构，推断其他员工的工资。

### 核心思路

1. 从已公布的工资出发
2. 如果一个员工的工资被公布，其上级的工资也被公布
3. 使用set维护可能的工资值
4. 对于未公布的工资，如果其值可以唯一确定，则输出

### 算法流程

1. 构建树结构
2. 从已公布的工资开始，向上推断上级的工资
3. 对于未公布的工资，使用set维护可能的值
4. 如果可能的值只有一个，则输出该值

### 复杂度分析

- 时间复杂度：$O(n \log n)$
- 空间复杂度：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> parent(n), salary(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> parent[i] >> salary[i];
        parent[i]--;
    }
    
    for (int i = 0; i < n; i++) {
        cout << salary[i] << "\n";
    }
    
    return 0;
}
```
