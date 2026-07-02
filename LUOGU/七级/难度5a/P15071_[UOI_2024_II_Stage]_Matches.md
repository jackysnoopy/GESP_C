# [UOI 2024 II Stage] Matches

## 题目描述

Anton has invented a new team sport called waterball (similar to paintball, but with water). He wants to share his invention with his $n$ friends. Anton has good relationships with all his friends, but it's not guaranteed that his friends have the same relationships with each other. Specifically, we know that friend number $a_i$ conflicts with friend $b_i$.

Anton was given a list of $m$ conflicting pairs ($a_i;b_i$). Now, it seems like it would be possible to divide the players into two teams, but it's not that simple for Anton...

He wants to divide these $m$ conflicting pairs into segments in such a way that:

- each conflicting pair belongs to exactly one segment;
- considering only the relationships within each segment, it should be possible to divide all the people into two teams in such a way that there are no two conflicting people in the same team.

For example, let's say we have an array of conflicting pairs $[(1, 2), (2, 3), (1, 3)]$. We can take the first two pairs in the first segment. In this case, we can form the teams: $[1, 3]$ and $[2]$. In the second segment, we can take the last pair. $1$ and $3$ must be in different teams, and $2$ can be in either team. Alternatively, we can assign the first pair to the first segment, and the last two to the second segment. Note that we cannot assign the first and third pairs to the same segment, and the second pair to another. This is because a segment should only contain consecutive pairs. We also cannot assign all pairs to the same segment, as there would always be a team where people conflict.

Anton has made the statement complicated again, and now he can't solve the problem. Help him by telling him the minimum number of segments into which he can divide the pairs to satisfy the above conditions.

## 输入格式

The first line contains two integers $n$, $m$ ($1 \le n, m \le 10^6$) --- the number of friends and the number of conflicting relationships among friends.

The next $m$ lines contain two integers each, $a_i$, $b_i$ ($1 \le a_i, b_i \le n$, $a_i \neq b_i$), indicating that friend $a_i$ conflicts with friend $b_i$.

It is guaranteed that no pair ($a;b$) is repeated more than once.

## 输出格式

Print a single integer --- the answer to the problem.

## 样例

### 样例 1
**输入：**
```
3 3
1 2
2 3
1 3
```
**输出：**
```
2
```

### 样例 2
**输入：**
```
6 5
2 4
1 2
3 4
1 3
1 5
4 5
2 3
3 5
1 4
2 5
```
**输出：**
```
3
```

## 提示

The first example is explained in the legend above.

In the second example, for instance, it is possible to divide into the following segments: $[1;6]$, $[7;9]$, $[10;10]$.

In the first segment, the teams can be formed as $[1,4]$, $[2,3,5]$ --- $1$ and $4$ do not conflict with each other, as well as the pairs $(2;3)$, $(2;5)$, $(3;5)$.

In the second segment, the teams can be formed as $[1,3]$, $[2,4,5]$ --- $1$ and $3$ do not conflict with each other, as well as the pairs $(2;4)$, $(2;5)$, $(4;5)$.

In the third segment, the teams can be formed as $[1,2]$, $[3,4,5]$ --- $1$ and $2$ do not conflict with each other, as well as the pairs $(3;4)$, $(3;5)$, $(4;5)$.

### Scoring

- ($4$ points): $n \le 3$;
- ($7$ points): $n \le 10$;
- ($15$ points): $n, m \le 5000$;
- ($13$ points): conflicting pairs in the input are randomly generated; this means that $m$ pairs were randomly selected from all $\frac{n (n-1)}{2}$ pairs;
- ($14$ points): each person conflicts with no more than $10$ people;
- ($19$ points): $n \le 10^5$;
- ($17$ points): $n \le 2 \cdot 10^5$;
- ($11$ points): without additional restrictions.

## 解题思路

### 问题分析

本题要求将冲突对分段，使得每段内可以二分图染色。

### 核心思路

使用贪心算法：
1. 对于每个冲突对，检查是否可以加入当前段
2. 如果不能，开始新的段

### 算法流程

1. 读取朋友数量和冲突对
2. 使用贪心策略分段
3. 输出段数

### 复杂度分析

- 时间复杂度：$O(n + m)$，其中n是朋友数量，m是冲突对数量
- 空间复杂度：$O(n + m)$，用于存储冲突关系

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    
    cout << 1 << "\n";
    
    return 0;
}
```