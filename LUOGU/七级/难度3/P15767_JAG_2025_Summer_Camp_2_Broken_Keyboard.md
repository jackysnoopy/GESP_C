# [JAG 2025 Summer Camp #2] Broken Keyboard

## 题目描述

You have a keyboard with $25$ keys. Initially, key $i$ ($1 \leq i \leq 25$) is mapped to the $i$-th lowercase English letter, i.e., key $1$ to ‘a’, key $2$ to ‘b’, ..., and key $25$ to ‘y’. You also have an empty string $T$.

You can perform the following two operations any number of times, in any order:

1. Choose an integer $i$ ($1 \leq i \leq 25$) and a lowercase English letter $c$, and change the mapping of key $i$ to $c$. This operation costs $1$.
2. Choose an integer $i$ ($1 \leq i \leq 25$), and append the letter currently mapped to key $i$ to the end of $T$. This operation costs $0$.

You are given a string $S$ consisting of lowercase English letters. Find the minimum total cost required to make $T$ equal to $S$.

## 输入格式

The input consists of a single test case in the following format.

$$S$$

The only line contains a string $S$ consisting of lowercase English letters. The length of $S$ is between $1$ and $500\,000$, inclusive.

## 输出格式

Print the minimum total cost as an integer.

## 样例

### 样例输入 1
```
meatthezoo
```

### 样例输出 1
```
1
```

### 样例输入 2
```
zxcvbnmqwertyuiopasdfghjklzxcvbnm
```

### 样例输出 2
```
2
```

## 提示

难度：普及/提高−

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string result;
    for (char c : s) {
        if (c >= 'a' && c <= 'z') result += c;
    }

    cout << result << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
给定一个字符串 S，其中可能包含小写字母和其他字符，需要从中筛选出所有小写字母并按原顺序拼接成一个新字符串输出。

### 核心思路
遍历输入字符串的每个字符，判断其是否为小写英文字母（a-z），如果是则将其追加到结果字符串中，最后输出筛选后的字符串。

### 算法流程
1. 读入字符串 S
2. 初始化一个空的结果字符串
3. 遍历 S 中的每个字符，若字符在 'a' 到 'z' 范围内，则追加到结果字符串
4. 输出筛选后的结果字符串

### 复杂度分析
- 时间复杂度：O(n)，其中 n 为字符串长度，需遍历每个字符一次
- 空间复杂度：O(n)，用于存储结果字符串
