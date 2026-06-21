# [USACO1.3] 最长的回文 Calf Flac

## 题目描述
据说如果你给无限只母牛和无限台巨型便携式电脑（有非常大的键盘 ), 那么母牛们会制造出世上最棒的回文。你的工作就是去寻找这些牛制造的奇观（最棒的回文）。

在寻找回文时不用理睬那些标点符号、空格（但应该保留下来以便做为答案输出）, 只用考虑字母 ${\tt A}\sim {\tt Z}$ 和 ${\tt a}\sim {\tt z}$。要你寻找的最长的回文的文章是一个不超过 $20{,}000$ 个字符的字符串。我们将保证最长的回文不会超过 $2{,}000$ 个字符（在除去标点符号、空格之前）。

## 输入格式
输入文件不会超过 $20,000$ 字符。这个文件可能一行或多行，但是每行都不超过 $80$ 个字符（不包括最后的换行符）。

## 输出格式
输出的第一行应该包括找到的最长的回文的长度。

下一行或几行应该包括这个回文的原文（没有除去标点符号、空格），把这个回文输出到一行或多行（如果回文中包括换行符）。

如果有多个回文长度都等于最大值，输出最前面出现的那一个。

## 样例
### 样例 1
```
Confucius say: Madam, I'm Adam. 
```
```
11
Madam, I'm Adam
```

## 提示
题目翻译来自NOCOW。

USACO Training Section 1.3

## 解题思路
### 问题分析
忽略标点和空格，找最长回文子串，输出原字符串中的内容和长度。

### 核心思路
中心扩展法。对每个字符和间隙作为中心向两边扩展。注意只考虑字母。

### 算法流程
1. 读入整个文本
2. 提取字母和对应原位置
3. 对每个中心扩展找最长回文
4. 输出最长回文的原字符串

### 复杂度分析
- 时间复杂度：O(n²)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text, line;
    while (getline(cin, line)) text += line + "\n";
    
    string letters;
    vector<int> pos;
    for (int i = 0; i < (int)text.size(); i++) {
        if (isalpha(text[i])) {
            letters += tolower(text[i]);
            pos.push_back(i);
        }
    }
    
    int n = letters.size(), best_len = 0, best_l = 0, best_r = 0;
    for (int c = 0; c < n; c++) {
        int l = c, r = c;
        while (l >= 0 && r < n && letters[l] == letters[r]) { l--; r++; }
        int len = r - l - 1;
        if (len > best_len) { best_len = len; best_l = l + 1; best_r = r - 1; }
        
        l = c; r = c + 1;
        while (l >= 0 && r < n && letters[l] == letters[r]) { l--; r++; }
        len = r - l - 1;
        if (len > best_len) { best_len = len; best_l = l + 1; best_r = r - 1; }
    }
    
    cout << best_len << "\n";
    for (int i = pos[best_l]; i <= pos[best_r]; i++)
        cout << text[i];
    return 0;
}
```
