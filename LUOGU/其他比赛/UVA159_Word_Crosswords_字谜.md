# UVA159 - Word Crosswords (字谜)

## 题目描述

将单词按照横向和纵向交替排列形成字谜网格。

## 输入格式

每组数据第一行一个整数 n，表示单词数量。接着 n 个单词。输入以 `0` 结尾。

## 输出格式

输出字谜网格，空格用空格填充。

## 样例

略。

## 解题思路

### 问题分析

将奇数位置的单词横向排列，偶数位置的单词纵向排列，形成交叉网格。

### 核心思路

1. 奇数索引单词横向放置
2. 偶数索引单词纵向放置
3. 输出网格中非空格部分

### 复杂度分析

- 时间复杂度：O(N * L)
- 空间复杂度：O(20 * 20)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << "\n";
        first = false;
        vector<string> words(n);
        for (int i = 0; i < n; i++) cin >> words[i];
        
        vector<string> h, v;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) h.push_back(words[i]);
            else v.push_back(words[i]);
        }
        
        vector<vector<char>> grid(20, vector<char>(20, ' '));
        int hr = 0;
        for (auto &w : h) {
            for (int j = 0; j < (int)w.size(); j++) {
                grid[hr][j + 2] = w[j];
            }
            hr += 2;
        }
        
        int vc = 0;
        for (auto &w : v) {
            for (int i = 0; i < (int)w.size(); i++) {
                grid[i + 2][vc] = w[i];
            }
            vc += 2;
        }
        
        for (int i = 0; i < 20; i++) {
            bool hasContent = false;
            for (int j = 0; j < 20; j++) {
                if (grid[i][j] != ' ') hasContent = true;
            }
            if (!hasContent) continue;
            for (int j = 0; j < 20; j++) {
                cout << grid[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}
```
