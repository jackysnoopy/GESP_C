# [CEOI 2022] Homework

## 题目描述

这是 Helena 的数学作业中的一道题：

我们定义合法表达式如下：

- `?` 是合法表达式，这表示一个未知数。
- 如果 $A,B$ 均为合法表达式，那么 $\texttt{min(}A\texttt{,}B\texttt{)}$ 和 $\texttt{max(}A\texttt{,}B\texttt{)}$ 均为合法表达式，这分别表示取左右两边的最大值/最小值。

设 `?` 的个数为 $N$，现在给出一个合法表达式，将每一个问号替换为 $1\sim N$ 中的任意一个数并且每一个数不能使用多次，可以得到多少种不同的答案？

## 输入格式

仅一行一个字符串表示给出的合法表达式。

## 输出格式

输出一个整数，表示不同答案的个数。

## 样例

### 样例1
**输入：**
```
min(min(?,?),min(?,?))
```
**输出：**
```
1
```

### 样例2
**输入：**
```
max(?,max(?,min(?,?)))
```
**输出：**
```
2
```

### 样例3
**输入：**
```
min(max(?,?),min(?,max(?,?)))
```
**输出：**
```
3
```

## 提示

**【数据规模与约定】**

对于全部数据，$2\le N\le 10^6$。

## 解题思路

### 问题分析

我们需要计算将表达式中的 `?` 替换为 $1 \sim N$ 的排列后，能得到多少种不同的结果。

### 核心思路

**动态规划 + 表达式树**

1. 将表达式解析为树结构
2. 对每个节点，计算其可能的结果集合
3. 使用 DP 计算最终答案

### 算法流程

1. 解析表达式，构建表达式树
2. 对每个 `?` 节点，其可能的结果是 $\{1, 2, \ldots, N\}$
3. 对 `min` 节点，结果是两个子节点结果的最小值
4. 对 `max` 节点，结果是两个子节点结果的最大值
5. 使用 DP 计算每个节点的可能结果集合大小
6. 输出根节点的可能结果集合大小

### 复杂度分析

- 时间复杂度：$O(N)$
- 空间复杂度：$O(N)$

## 参考代码

```cpp
#include <cstdio>
#include <algorithm>
#include <string>
#include <stack>
#include <iostream>
using namespace std;
struct Node {
    char type;
    int left, right;
    int min_rank, max_rank;
};
const int MAXN = 2000005;
Node nodes[MAXN];
int node_cnt = 0;
int parse(const string& s, int& pos) {
    int cur = node_cnt++;
    if (s[pos] == '?') {
        nodes[cur].type = '?';
        nodes[cur].min_rank = 1;
        nodes[cur].max_rank = 1;
        pos++;
        return cur;
    }
    if (s.substr(pos, 4) == "min(") {
        nodes[cur].type = 'm';
        pos += 4;
    } else {
        nodes[cur].type = 'M';
        pos += 4;
    }
    nodes[cur].left = parse(s, pos);
    pos++;
    nodes[cur].right = parse(s, pos);
    pos++;
    return cur;
}
void compute(int u) {
    if (nodes[u].type == '?') return;
    compute(nodes[u].left);
    compute(nodes[u].right);
    int l = nodes[u].left, r = nodes[u].right;
    if (nodes[u].type == 'm') {
        nodes[u].min_rank = min(nodes[l].min_rank, nodes[r].min_rank);
        nodes[u].max_rank = max(nodes[l].max_rank, nodes[r].max_rank);
    } else {
        nodes[u].min_rank = max(nodes[l].min_rank, nodes[r].min_rank);
        nodes[u].max_rank = min(nodes[l].max_rank, nodes[r].max_rank);
    }
}
int main() {
    string s;
    getline(cin, s);
    int pos = 0;
    int root = parse(s, pos);
    compute(root);
    int n = 0;
    for (int i = 0; i < node_cnt; i++) {
        if (nodes[i].type == '?') n++;
    }
    printf("%d\n", max(0, nodes[root].max_rank - nodes[root].min_rank + 1));
    return 0;
}
```