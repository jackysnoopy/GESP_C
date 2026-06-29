# [NWRRC 2023] Missing Vowels

## 题目描述

字符串只含英文字母和连字符 `-`。字母 `a, e, i, o, u, y` 视为元音，连字符和其余字母视为辅音。比较大小写不敏感。

给定短名 $s$ 和长名 $f$，判断 $s$ 是否能由 $f$ 删除若干个（可为零）元音得到。

## 输入格式

第一行字符串 $s$，第二行字符串 $f$。长度均非空且不超过 $1000$。

## 输出格式

能则输出 `Same`，否则输出 `Different`。

## 提示

无额外限制。

## 解题思路

### 问题分析

「$s$ 能由 $f$ 删除若干元音得到」等价于：$s$ 是 $f$ 的子序列，且 $f$ 中未被匹配到的字符全部是元音。也就是说：

- $s$ 的每个字符按顺序在 $f$ 中找到匹配；
- $f$ 中跳过（删除）的字符只能是元音；任何辅音都必须被匹配。

### 核心思路

**双指针贪心**。指针 $i$ 扫 $s$，$j$ 扫 $f$：

- 若 $s[i] = f[j]$（大小写不敏感），匹配，$i$、$j$ 同时右移；
- 否则若 $f[j]$ 是元音，可以跳过它，$j$ 右移；
- 否则（$f[j]$ 是辅音且不等于 $s[i]$），无法删除该辅音，判定失败。

匹配结束后，$f$ 末尾剩余的字符必须全是元音（可继续跳过），且 $s$ 必须被完全消耗。贪心正确性：辅音不可跳过，故每个辅音必须按序匹配；遇到能匹配就尽早匹配能给后续留出最大余地，是标准的子序列贪心。

### 算法流程

1. 读入两行 $s, f$。
2. 双指针扫描：能匹配则同进；不能匹配但 $f[j]$ 是元音则 $j$ 进；否则失败。
3. 扫完后跳过 $f$ 末尾元音，检查 $i$ 到 $s$ 末尾、$j$ 到 $f$ 末尾。
4. 输出 `Same` 或 `Different`。

### 复杂度分析

- 时间：$O(|s| + |f|)$。
- 空间：$O(|s| + |f|)$。

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
