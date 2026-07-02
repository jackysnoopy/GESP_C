# UVA123 - Searching Quickly (快速搜索)

## 题目描述

给定一组关键词（不区分大小写，需要在搜索时忽略）和一段文本，找出文本中所有关键词的出现位置。对于每次出现，输出关键词及其上下文（前 5 个字符和后 5 个字符，超出文本范围则取到边界）。关键词之间不应重叠。按在文本中出现的位置排序输出。

## 输入格式

- 第一部分：关键词列表，每行一个关键词，最后一行为 `:`
- 第二部分：文本内容，多行
- 输入以 `#` 结束

## 输出格式

- 每行输出一次关键词匹配
- 关键词以大写形式显示
- 关键词前后各显示 5 个字符作为上下文
- 超出文本范围的部分不显示
- 按匹配位置在文本中的顺序输出

## 样例

### 输入
```
:
a
an
the
some
*
sample text for
demonstration

#
```

### 输出
```
a SAMPLE TEXT FOR
AN SAMPLE TEXT FOR
SOME SAMPLE TEXT FOR
A DEMONSTRATION
AN DEMONSTRATION
```

## 解题思路

### 问题分析

本题要求在文本中搜索所有关键词的出现位置，并显示上下文。需要注意：
1. 关键词不区分大小写
2. 输出时关键词以大写形式显示
3. 上下文中的换行符应替换为空格
4. 关键词不应重叠

### 核心思路

1. **读入数据**：先读入所有关键词，再读入文本内容
2. **文本拼接**：将所有文本行拼接为一个字符串，方便搜索
3. **关键词搜索**：对每个关键词在文本中查找所有出现位置
4. **去重排序**：按位置排序，移除重叠的匹配
5. **输出结果**：根据位置输出上下文和关键词

### 算法流程

1. 读取关键词列表（直到遇到 `:`）
2. 读取文本内容（直到遇到 `#`）
3. 将文本拼接为单一字符串，记录每行的起始位置
4. 对每个关键词在文本中查找所有出现位置
5. 按位置排序，移除重叠匹配
6. 对每个匹配，提取前 5 和后 5 个字符作为上下文
7. 将换行符替换为空格，输出结果

### 复杂度分析

- 时间复杂度：O(N × M)，其中 N 为文本长度，M 为关键词数量
- 空间复杂度：O(N)，用于存储文本和匹配结果

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string toLower(const string& s) {
    string res = s;
    for (auto& c : res) c = tolower(c);
    return res;
}

string toUpper(const string& s) {
    string res = s;
    for (auto& c : res) c = toupper(c);
    return res;
}

struct Match {
    int pos;
    int len;
    string keyword;
    bool operator<(const Match& o) const { return pos < o.pos; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    vector<string> keywords;
    bool firstCase = true;

    while (getline(cin, line)) {
        if (line == "#") break;

        if (line.empty() || line.back() == ':') {
            if (!line.empty() && line.back() == ':')
                line.pop_back();
            if (!line.empty())
                keywords.push_back(line);
            if (line.empty()) {
                if (!firstCase) cout << "\n";
                firstCase = false;

                vector<string> text;
                string tl;
                while (getline(cin, tl) && tl != "#") {
                    text.push_back(tl);
                }

                string full;
                vector<int> lineStart;
                for (int i = 0; i < (int)text.size(); i++) {
                    lineStart.push_back((int)full.size());
                    full += text[i] + "\n";
                }

                string lowerFull = toLower(full);
                vector<Match> matches;

                for (auto& kw : keywords) {
                    string lk = toLower(kw);
                    size_t pos = 0;
                    while ((pos = lowerFull.find(lk, pos)) != string::npos) {
                        matches.push_back({(int)pos, (int)lk.size(), kw});
                        pos += lk.size();
                    }
                }

                sort(matches.begin(), matches.end());

                vector<Match> result;
                int lastEnd = -1;
                for (auto& m : matches) {
                    if (m.pos >= lastEnd) {
                        result.push_back(m);
                        lastEnd = m.pos + m.len;
                    }
                }

                for (auto& m : result) {
                    int ctxStart = max(0, m.pos - 5);
                    int ctxEnd = min((int)full.size(), m.pos + m.len + 5);
                    string prefix = full.substr(ctxStart, m.pos - ctxStart);
                    string suffix = full.substr(m.pos + m.len, ctxEnd - m.pos - m.len);

                    for (int i = 0; i < (int)prefix.size(); i++) {
                        if (prefix[i] != '\n') cout << prefix[i];
                        else cout << " ";
                    }
                    cout << toUpper(m.keyword);
                    for (int i = 0; i < (int)suffix.size(); i++) {
                        if (suffix[i] != '\n') cout << suffix[i];
                        else cout << " ";
                    }
                    cout << "\n";
                }

                keywords.clear();
                break;
            }
        }
    }

    return 0;
}
```
