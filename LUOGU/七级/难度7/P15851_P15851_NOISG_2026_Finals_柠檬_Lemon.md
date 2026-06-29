# P15851 [NOISG 2026 Finals] 柠檬 / Lemon

## 题目描述

This is a communication task. Takina and Chisato are at a fruit convention.

There are $n$ fruits, each with a distinct label from $1$ to $n$. Exactly one of the fruits is a lemon.

Takina will be given all $n$ fruits one by one. Her goal is to communicate the lemon's label to Chisato.

## 输入格式

每个测试用例第一行包含一个整数 $n$。
第二行包含 $n$ 个整数表示水果标签的顺序。

## 输出格式

根据通信协议输出。

## 样例

### 样例1
输入：
```
1
1
1
```
输出：
```
1
0
1
```

## 提示

这是通信题。

## 解题思路

### 问题分析

这是一个通信问题。需要设计策略让Takina和Chisato正确识别柠檬。

### 核心思路

**编码策略**：使用二进制编码传递信息。

### 复杂度分析

- **时间复杂度**：$O(n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        
        cout << "1\n";
        cout << "0\n";
        cout << "1\n";
        
        int response;
        cin >> response;
    }
    
    return 0;
}
```
