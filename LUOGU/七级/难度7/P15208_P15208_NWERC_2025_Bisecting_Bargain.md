# P15208 [NWERC 2025] Bisecting Bargain

## 题目描述

艾米莉亚和亚历克斯喜欢圣诞市场。他们需要从取款机提取现金。

取款机可以支付所有可能的欧元硬币和纸币，面值从 $1$ 欧元起：$1$ 欧元、$2$ 欧元、$5$ 欧元、$10$ 欧元、$20$ 欧元、$50$ 欧元、$100$ 欧元、$200$ 欧元和 $500$ 欧元。

如果他们从取款机提取 $n$ 欧元，钱是否总是可以平均分配？

## 输入格式

一行，一个整数 $n$，表示想要提取的现金总额。

## 输出格式

如果钱总是可以平均分配，输出"splittable"。否则输出"unsplittable"。

## 样例

### 样例1
输入：
```
42
```
输出：
```
unsplittable
```

### 样例2
输入：
```
40
```
输出：
```
splittable
```

## 提示

$1 \le n \le 10000$。

## 解题思路

### 问题分析

这是一个数论问题。需要判断是否总是可以平均分配。

### 核心思路

**贪心策略**：检查是否总是可以分成两半。

### 复杂度分析

- **时间复杂度**：$O(1)$
- **空间复杂度**：$O(1)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n % 2 == 0) {
        cout << "splittable\n";
    } else {
        cout << "unsplittable\n";
    }
    
    return 0;
}
```
