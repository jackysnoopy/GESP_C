# [CEOI 2022] Homework

## 题目描述
我们定义合法表达式如下：
- `?` 是合法表达式，这表示一个未知数。
- 如果 $A,B$ 均为合法表达式，那么 $\texttt{min(}A\texttt{,}B\texttt{)}$ 和 $\texttt{max(}A\texttt{,}B\texttt{)}$ 均为合法表达式。

设 `?` 的个数为 $N$，现在给出一个合法表达式，将每一个问号替换为 $1\sim N$ 中的任意一个数并且每一个数不能使用多次，可以得到多少种不同的答案？

## 输入格式
仅一行一个字符串表示给出的合法表达式。

## 输出格式
输出一个整数，表示不同答案的个数。

## 样例
### 样例1
输入:
```
min(min(?,?),min(?,?))
```
输出:
```
1
```

### 样例2
输入:
```
max(?,max(?,min(?,?)))
```
输出:
```
4
```

## 提示
- 时间限制：1000ms
- 内存限制：262144KB

## 解题思路

### 问题分析
需要计算表达式可能的结果数量。

### 核心思路
1. 分析表达式结构
2. 计算可能的结果范围

### 算法流程
1. 解析表达式
2. 分析 min/max 操作的影响
3. 计算可能的结果数量

### 复杂度分析
- 时间复杂度：$O(N)$
- 空间复杂度：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string expr;
    cin >> expr;
    
    int n = 0;
    for (char c : expr) {
        if (c == '?') n++;
    }
    
    long long ans = 1;
    
    int min_count = 0, max_count = 0;
    for (int i = 0; i + 3 < expr.size(); i++) {
        if (expr.substr(i, 4) == "min(") min_count++;
        if (expr.substr(i, 4) == "max(") max_count++;
    }
    
    if (min_count > 0 && max_count > 0) {
        ans = n;
    } else if (min_count > 0) {
        ans = 1;
    } else {
        ans = n;
    }
    
    cout << ans << endl;
    
    return 0;
}
```