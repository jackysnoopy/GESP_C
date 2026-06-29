# [NWRRC 2023] Missing Vowels

## 题目描述

There are many ways to write a word on paper. For example, some writing systems, like Arabic and Hebrew, omit most vowels, although they write some of them.

In this problem, we will only consider strings consisting of English letters and hyphens. Letters $\tt{a}$, $\tt{e}$, $\tt{i}$, $\tt{o}$, $\tt{u}$, and $\tt{y}$ are considered to be vowels, while hyphens and all other letters are considered to be consonants. All comparisons are case-insensitive: uppercase and lowercase versions of the same letter are considered equal.

You are given two strings $s$ and $f$, called the $\textit{short}$ name and the $\textit{full}$ name, respectively. Your task is to check whether the short name $s$ can be obtained from the full name $f$ by omitting some vowels (possibly none).

## 输入格式

The first line contains a single string $s$, denoting the short name.

The second line contains a single string $f$, denoting the full name.

Each string is non-empty and consists of at most $1000$ English letters and hyphens.

## 输出格式

Print $\tt{Same}$ if the short name $s$ can be obtained from the long name $f$ by omitting some vowels, and $\tt{Different}$ otherwise.

## 样例

### 样例输入 1
```
Shrm-el-Shikh
Sharm-el-Sheikh
```

### 样例输出 1
```
Same
```

### 样例输入 2
```
Eilot
Eilat
```

### 样例输出 2
```
Different
```

### 样例输入 3
```
Saint-Petersburg
Saint-Petersburg
```

### 样例输出 3
```
Same
```

### 样例输入 4
```
Bcdfghjklmnpqrstvwxz
Abcdefghijklmnopqrstuvwxzyy
```

### 样例输出 4
```
Same
```

### 样例输入 5
```
Aa
aaaA
```

### 样例输出 5
```
Same
```

### 样例输入 6
```
Etis-Atis-Amatis
Etis-Atis-Animatis
```

### 样例输出 6
```
Different
```

### 样例输入 7
```
will-the-wisp
will-o-the-wisp
```

### 样例输出 7
```
Different
```

### 样例输入 8
```
--a-very-short-name--
long-name
```

### 样例输出 8
```
Different
```

## 提示



## 解题思路

### 问题分析
待补充

### 核心思路
待补充

### 算法流程
待补充

### 复杂度分析
待补充

## 参考代码

```cpp
#include <iostream>
#include <string>
using namespace std;
bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}
int main() {
    string s, f;
    getline(cin, s);
    getline(cin, f);
    int i = 0, j = 0;
    bool ok = true;
    while (i < (int)s.size() && j < (int)f.size()) {
        char sc = tolower(s[i]), fc = tolower(f[j]);
        if (sc == fc) { i++; j++; }
        else if (isVowel(f[j])) j++;
        else { ok = false; break; }
    }
    if (ok) {
        while (j < (int)f.size() && isVowel(f[j])) j++;
        if (i < (int)s.size()) ok = false;
        if (j < (int)f.size()) ok = false;
    }
    cout << (ok ? "Same" : "Different") << "\n";
    return 0;
}
```