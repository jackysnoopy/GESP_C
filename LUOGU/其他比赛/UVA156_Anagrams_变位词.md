# UVA156 - Anagrams (变位词)

## 题目描述

给出一个单词列表，找出其中所有"anagram"（变位词）只出现一次的单词。变位词是指两个单词包含完全相同的字母（不区分大小写）。输出这些单词，按字典序排序。

## 输入格式

每行一个单词，以 `#` 结尾。单词只包含大小写字母。

## 输出格式

按字典序输出所有"独一无二"的变位词（即该变位词组中只出现一次的单词）。

## 样例

输入：
```
ladder
tack
act
more
come
#
```

输出：
```
act
come
ladder
more
```

## 提示

- 单词数量不超过1000
- 每个单词长度不超过20

## 解题思路

### 问题分析

判断两个单词是否为变位词，只需将字母排序后比较。统计每个变位词组的出现次数，只输出出现一次的。

### 核心思路

1. 将每个单词转为小写后排序，作为变位词的key
2. 用map分组统计
3. 筛选只出现一次的变位词组
4. 按字典序输出

### 算法流程

1. 读入所有单词
2. 对每个单词，转小写并排序得到key
3. 按key分组
4. 输出大小为1的组中的单词

### 复杂度分析

- 时间复杂度：O(N * K * logK)，N为单词数，K为单词长度
- 空间复杂度：O(N * K)

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

string toLower(string s) {
    for (auto &c : s) c = tolower(c);
    return s;
}

int main() {
    string word;
    map<string, vector<string>> groups;
    while (cin >> word && word != "#") {
        string key = toLower(word);
        sort(key.begin(), key.end());
        groups[key].push_back(word);
    }
    vector<string> result;
    for (auto &p : groups) {
        if (p.second.size() == 1) {
            result.push_back(p.second[0]);
        }
    }
    sort(result.begin(), result.end());
    for (auto &w : result) {
        cout << w << "\n";
    }
    return 0;
}
```
