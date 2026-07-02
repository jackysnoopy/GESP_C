# UVA162 - Belonging (归属)

## 题目描述

给定一个字典和一系列查询单词，判断每个查询单词是否在字典中。

## 输入格式

字典：每行一个单词，以 `#` 结尾。
查询：每行一个单词，以 `#` 结尾。
输入以 `#` 行结束。

## 输出格式

对每个查询单词，输出是否在字典中。

## 样例

略。

## 解题思路

### 问题分析

基本的字符串查找问题。

### 核心思路

1. 读入字典建立集合
2. 对每个查询判断是否在集合中

### 复杂度分析

- 时间复杂度：O(D + Q)，D为字典大小，Q为查询数
- 空间复杂度：O(D)

## 参考代码

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    while (line != "#") {
        set<string> dictionary;
        while (line != "#") {
            dictionary.insert(line);
            getline(cin, line);
        }
        string word;
        cin >> word;
        while (word != "#") {
            bool found = dictionary.count(word) > 0;
            cout << word << " is " << (found ? "in" : "not in") << " the dictionary.\n";
            cin >> word;
        }
        cin.ignore();
        getline(cin, line);
    }
    return 0;
}
```
