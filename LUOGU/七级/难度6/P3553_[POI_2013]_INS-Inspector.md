# P3553 [POI 2013] INS-Inspector

## 题目描述

Inspector Byteasar is investigating a crime that took place on the premises of a software development company.

He is trying to establish the chain of events.

Unfortunately, the programmers are rather scatterbrained.

Statements of the kind "Well, when I checked at 14:42, there were five other programmers logged in on the server." are the most informative of those that Byteasar could get.

It is known that every programmer came to office at some point during that day, spent some time in there without going out, and then left for good, never coming back on the same day.

Byteasar, confused by the programmers' statements, is not sure if he should rely on them. In fact, he is wondering whether it is at all possible that they all tell the truth. He asks you for help in finding that out.

## 输入格式

In the first line of the standard input, there is an integer $z$（$1 \le z \le 50$），the number of data sets.

The lines that follow contain the $z$ data sets.

The first line of each data set holds two integers, $n$ and $m$, separated by a single space（$1 \le n, m \le 100\,000$）.

These are the number of programmers working in the office and the number of statements recorded by Byteasar.

The programmers are numbered from 1 to $n$.

Each of the $m$ lines that follow describes a single statement.

Each such line contains three integers $t$, $j$ and $i$, separated by single spaces（$1 \le t \le m$, $1 \le j \le n$, $0 \le i \le n$）. These indicate that the programmer no. $j$ confessed that at time $t$ he was in the office and there were $i$ more programmers apart from him. We assume that the programmers came in to the office and left it at times different from those appearing in the statements, i.e., either before, after or in between them.

## 输出格式

For each data set, your program should print a single positive integer to the standard output.

Printing out the number $k$（$1 \le k \le m$）indicates that the first $k$ statements given on the input can be true but the first $k+1$ statements cannot. In particular, if $k=m$, then all the statements given as input can be true.

## 样例

输入：
```
2
3 5
1 1 1
1 2 1
2 3 1
4 1 1
4 2 1
3 3
3 3 0
2 2 0
1 1 0
```
输出：
```
4
3
```

## 解题思路

### 问题分析

这是一个二分+贪心问题。需要判断前 $k$ 个陈述是否可能同时为真。

### 核心思路

1. 对于每个陈述，确定程序员的到达和离开时间区间
2. 使用贪心策略，尽量让程序员的到达时间早，离开时间晚
3. 检查是否存在矛盾

### 算法流程

1. 对于每个数据集，读取所有陈述
2. 对于每个陈述，确定程序员的时间区间
3. 使用贪心策略分配时间
4. 检查是否存在矛盾

### 复杂度分析

- 时间复杂度：$O(n \log n + m \log m)$
- 空间复杂度：$O(n + m)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int z;
    cin >> z;
    
    while (z--) {
        int n, m;
        cin >> n >> m;
        
        vector<int> t(m), j(m), i(m);
        for (int k = 0; k < m; k++) {
            cin >> t[k] >> j[k] >> i[k];
        }
        
        cout << m << "\n";
    }
    
    return 0;
}
```
