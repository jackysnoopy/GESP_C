# UVA157 - Crossword Answers (填字游戏答案)

## 题目描述

给定一个填字游戏的网格，`#` 表示黑色方块，其他字符表示字母。找出所有横向和纵向的单词并按顺序输出。

## 输入格式

每组数据第一行两个整数 r c（行数和列数），接着 r 行每行 c 个字符。输入以 `0 0` 结尾。

## 输出格式

先输出 "Across"，再依次输出所有横向单词。
再输出 "Down"，再依次输出所有纵向单词。

## 样例

输入：
```
2 2
AT
*#
0 0
```

输出：
```
Across
AT
Down
A
```

## 提示

- 横向单词：从一个格子开始，向右连续至少2个非黑色格子
- 纵向单词：从一个格子开始，向下连续至少2个非黑色格子

## 解题思路

### 问题分析

遍历网格，识别横向和纵向单词的起始位置。

### 核心思路

1. 横向：格子左边是`#`或边界，且右边有至少一个非`#`格
2. 纵向：格子上边是`#`或边界，且下边有至少一个非`#`格

### 算法流程

1. 遍历每个格子
2. 判断是否为横向/纵向单词起始
3. 提取完整单词

### 复杂度分析

- 时间复杂度：O(r * c)
- 空间复杂度：O(r * c)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int r, c;
    bool first = true;
    while (cin >> r >> c && (r || c)) {
        if (!first) cout << "\n";
        first = false;
        vector<string> grid(r);
        for (int i = 0; i < r; i++) cin >> grid[i];
        
        vector<string> across, down;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] != '#') {
                    bool startAcross = (j == 0 || grid[i][j-1] == '#');
                    bool startDown = (i == 0 || grid[i-1][j] == '#');
                    if (startAcross && j + 1 < c && grid[i][j+1] != '#') {
                        string word = "";
                        for (int k = j; k < c && grid[i][k] != '#'; k++) word += grid[i][k];
                        across.push_back(word);
                    }
                    if (startDown && i + 1 < r && grid[i+1][j] != '#') {
                        string word = "";
                        for (int k = i; k < r && grid[k][j] != '#'; k++) word += grid[k][j];
                        down.push_back(word);
                    }
                }
            }
        }
        cout << "Across\n";
        for (auto &w : across) cout << w << "\n";
        cout << "Down\n";
        for (auto &w : down) cout << w << "\n";
    }
    return 0;
}
```
