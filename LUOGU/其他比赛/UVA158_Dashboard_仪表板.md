# UVA158 - Dashboard (仪表板)

## 题目描述

给定一个整数，统计其数字位数并输出相关信息。

## 输入格式

每行一个整数，以 `-1` 结尾。

## 输出格式

输出该数字的位数信息。

## 样例

略。

## 解题思路

### 问题分析

统计整数的非零数字位数。

### 核心思路

1. 将数字拆分为各个位
2. 统计非零位的数量
3. 输出结果

### 复杂度分析

- 时间复杂度：O(logN)
- 空间复杂度：O(logN)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n && n != -1) {
        if (!first) cout << "\n";
        first = false;
        vector<int> digits;
        int tmp = n;
        while (tmp > 0) {
            digits.push_back(tmp % 10);
            tmp /= 10;
        }
        reverse(digits.begin(), digits.end());
        int len = digits.size();
        int cnt = 0;
        for (int i = 0; i < len; i++) {
            if (digits[i] != 0) cnt++;
        }
        cout << n << " is " << cnt << "-digital number.\n";
    }
    return 0;
}
```
