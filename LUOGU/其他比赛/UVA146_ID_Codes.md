# UVA146 - ID Codes (ID代码)

## 题目描述
给定一个字符串，找到它的下一个字典序排列。如果不存在下一个排列，则输出"No Successor"。

## 解题思路

### 问题分析
这是一个经典的"下一个排列"问题，需要找到当前字符串在字典序中的下一个排列。

### 核心思路
使用C++标准库中的`next_permutation`函数，该函数实现了字典序下一个排列的算法。

### 算法流程
1. 读入字符串。
2. 调用`next_permutation`函数尝试获取下一个排列。
3. 如果成功，输出新排列；否则输出"No Successor"。

### 复杂度分析
- 时间复杂度：O(n)，其中n是字符串长度。
- 空间复杂度：O(1)。

## 代码实现
```cpp
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (cin >> s && s != "#") {
        if (next_permutation(s.begin(), s.end())) {
            cout << s << endl;
        } else {
            cout << "No Successor" << endl;
        }
    }

    return 0;
}
```
