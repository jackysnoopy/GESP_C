# UVA148 - Anagram (变位词)

## 题目描述
给定一个字典和测试词，对于每个测试词，找出字典中所有与该测试词包含相同字母的变位词。
输入格式：字典单词（每行一个），然后一个空行，然后测试单词。
输出格式：测试词: 字典词1 字典词2...

## 解题思路

### 问题分析
需要判断两个单词是否为变位词（包含相同字母，但顺序可以不同）。

### 核心思路
比较两个单词的字母频率是否相同。

### 算法流程
1. 读取字典中的所有单词。
2. 读取所有测试单词。
3. 对于每个测试单词，遍历字典，找出所有变位词。
4. 输出结果。

### 复杂度分析
- 时间复杂度：O(n*m)，其中n是测试单词数量，m是字典单词数量。
- 空间复杂度：O(1)。

## 代码实现
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool isAnagram(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;
    
    vector<int> count1(26, 0), count2(26, 0);
    for (char c : word1) count1[c - 'A']++;
    for (char c : word2) count2[c - 'A']++;
    
    return count1 == count2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    vector<string> dictionary;
    
    while (getline(cin, line) && line != "") {
        dictionary.push_back(line);
    }
    
    vector<string> test_words;
    while (getline(cin, line)) {
        test_words.push_back(line);
    }
    
    for (const string& test_word : test_words) {
        cout << test_word << ": ";
        
        vector<string> anagrams;
        for (const string& dict_word : dictionary) {
            if (dict_word != test_word && isAnagram(test_word, dict_word)) {
                anagrams.push_back(dict_word);
            }
        }
        
        for (size_t i = 0; i < anagrams.size(); ++i) {
            if (i > 0) cout << " ";
            cout << anagrams[i];
        }
        cout << endl;
    }
    
    return 0;
}
```
