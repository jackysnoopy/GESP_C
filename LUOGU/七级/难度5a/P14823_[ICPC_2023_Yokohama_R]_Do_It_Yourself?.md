# [ICPC 2023 Yokohama R] Do It Yourself?

## 题目描述

You are the head of a group of $n$ employees including you in a company. Each employee has an employee ID, which is an integer 1 through $n$, where your ID is 1. Employees are often called by their IDs for short: $\#1$, $\#2$, and so on. Every employee other than you has a unique *immediate boss*, whose ID is smaller than his/hers. A *boss* of an employee is transitively defined as follows.

- If an employee $\#i$ is the immediate boss of an employee $\#j$, then $\#i$ is a boss of $\#j$.
- If $\#i$ is a boss of $\#j$ and $\#j$ is a boss of $\#k$, then $\#i$ is a boss of $\#k$.

Every employee including you is initially assigned exactly one task. That task can be done by him/herself or by any one of his/her bosses. Each employee can do an arbitrary number of tasks, but doing many tasks makes the employee too tired. Formally, each employee $\#i$ has an individual fatigability constant $f_i$, and if $\#i$ does $m$ tasks in total, then the *fatigue level* of $\#i$ will become $f_i \times m^2$.

Your mission is to minimize the sum of fatigue levels of all the $n$ employees.

## 输入格式

The input consists of a single test case in the following format.

$$
\begin{aligned}
& n \\
& b_2 \ b_3 \ \cdots \ b_n \\ 
& f_1 \ f_2 \ \cdots \ f_n \\
\end{aligned}
$$

The integer $n$ in the first line is the number of employees, where $2 \leq n \leq 5 \times 10^5$. The second line has $n-1$ integers $b_i$ ($2 \leq i \leq n$), each of which represents the immediate boss of the employee $\#i$, where $1 \leq b_i < i$. The third line has $n$ integers $f_i$ ($1 \leq i \leq n$), each of which is the fatigability constant of the employee $\#i$, where $1 \leq f_i \leq 10^{12}$.

## 输出格式

Output the minimum possible sum of fatigue levels of all the $n$ employees.

## 样例

### 样例 1
**输入：**
```
4
1 1 2
1 1 1 1
```
**输出：**
```
4
```

### 样例 2
**输入：**
```
4
1 1 2
1 10 10 10
```
**输出：**
```
16
```

### 样例 3
**输入：**
```
4
1 1 2
1 2 4 8
```
**输出：**
```
10
```

## 提示

![Figure J.1. Illustration of the three samples (from left to right)](https://cdn.luogu.com.cn/upload/image_hosting/2uyilpky.png)

The situations and solutions of the three samples are illustrated in Figure J.1.

For Sample Input 1, the unique optimal way is that each employee does his/her task by him/herself. That is, you should just say "Do it yourself!" to everyone.

For Sample Input 2, the unique optimal way is that the employee $\#1$ does all the tasks. That is, you should just say "Leave it to me!" to everyone.

For Sample Input 3, one of the optimal ways is the following.

- $\#1$ does the tasks of $\#1$ and $\#2$, and then the fatigue level of $\#1$ will be $1 \times 2^2 = 4$.
- $\#2$ does the task of $\#4$, and then the fatigue level of $\#2$ will be $2 \times 1^2 = 2$.
- $\#3$ does the initially assigned task, and then the fatigue level of $\#3$ will be $4 \times 1^2 = 4$.
- $\#4$ does nothing, and then the fatigue level of $\#4$ will be $8 \times 0^2 = 0$.

Thus, the sum of the fatigue levels is $4 + 2 + 4 + 0 = 10$. There is another optimal way, in which the employees $\#1$, $\#2$, and $\#3$ do their initially assigned tasks by themselves and $\#1$ does the task of $\#4$ in addition.

## 解题思路

### 问题分析

本题要求在树形结构中分配任务，使得所有员工的疲劳度之和最小。每个员工可以自己完成任务，也可以由其上司完成。

### 核心思路

使用树形DP：
1. 定义dp[u][0]表示以u为根的子树中，u不做任务时的最小疲劳度
2. 定义dp[u][1]表示以u为根的子树中，u做任务时的最小疲劳度
3. 对于每个节点，计算两种状态的最小值

### 算法流程

1. 构建树结构
2. 进行DFS遍历
3. 对于每个节点，计算dp[u][0]和dp[u][1]
4. 返回根节点的最小疲劳度

### 复杂度分析

- 时间复杂度：$O(n)$，其中n是员工数量
- 空间复杂度：$O(n)$，用于存储树结构和DP数组

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> children[MAXN];
long long f[MAXN];
long long dp[MAXN][2];

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = f[u];
    
    for (int v : children[u]) {
        dfs(v);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        int b;
        cin >> b;
        children[b].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> f[i];
    }
    
    dfs(1);
    
    cout << min(dp[1][0], dp[1][1]) << "\n";
    
    return 0;
}
```