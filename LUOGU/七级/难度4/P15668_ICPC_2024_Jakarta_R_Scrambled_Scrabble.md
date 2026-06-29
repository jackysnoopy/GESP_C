# [ICPC 2024 Jakarta R] Scrambled Scrabble

## 题目描述

You are playing a word game using a standard set of $ 26 $ uppercase English letters: A — Z. In this game, you can form vowels and consonants as follows.

- The letters A, E, I, O, and U can only form a vowel.
- The letter Y can form either a vowel or a consonant.
- Each of the remaining letters other than A, E, I, O, U, and Y can only form a consonant.
- The string NG can form a single consonant when concatenated together.

Denote a syllable as a concatenation of a consonant, a vowel, and a consonant in that order. A word is a concatenation of one or more syllables.

You are given a string $ S $ and you want to create a word from it. You are allowed to delete zero or more letters from $ S $ and rearrange the remaining letters to form the word. Find the length of the longest word that can be created, or determine if no words can be created.

## 输入格式

A single line consisting of a string $ S $ ( $ 1 \leq |S| \leq 5000 $ ). The string $ S $ consists of only uppercase English letters.

## 输出格式

If a word cannot be created, output 0. Otherwise, output a single integer representing the length of longest word that can be created.

## 样例

### 样例输入 1
```
ICPCJAKARTA
```

### 样例输出 1
```
9
```

### 样例输入 2
```
NGENG
```

### 样例输出 2
```
5
```

### 样例输入 3
```
YYY
```

### 样例输出 3
```
3
```

### 样例输入 4
```
DANGAN
```

### 样例输出 4
```
6
```

### 样例输入 5
```
AEIOUY
```

### 样例输出 5
```
0
```

## 提示

Explanation for the sample input/output #1

A possible longest word is JAKCARTAP, consisting of the syllables JAK, CAR, and TAP.

Explanation for the sample input/output #2

The whole string $ S $ is a word consisting of one syllable which is the concatenation of the consonant NG, the vowel E, and the consonant NG.

Explanation for the sample input/output #3

The whole string $ S $ is a word consisting of one syllable which is the concatenation of the consonant Y, the vowel Y, and the consonant Y.

Explanation for the sample input/output #4

The whole string $ S $ is a word consisting of two syllables: DAN and GAN.

## 解题思路

### 问题分析
给定字符串 S，可以删除和重排字母来构造"单词"。单词由音节组成，音节 = 辅音+元音+辅音。Y 可作元音或辅音，NG 连在一起算一个辅音。求最长单词长度。

### 核心思路
统计元音数（A/E/I/O/U + Y）和辅音数（其他 + NG 对）。每个音节需要 2 个辅音和 1 个元音，最多能构成 min(辅音/2, 元音) 个音节，单词长度 = 音节数 × 3。

### 算法流程
1. 遍历字符串，统计：
   - vowels：A/E/I/O/U 的数量
   - y_count：Y 的数量
   - ng_count：NG 对的数量
   - consonants：其他辅音数量
2. total_consonants = consonants + ng_count
3. total_vowels = vowels + y_count
4. syllables = min(total_consonants / 2, total_vowels)
5. 输出 syllables × 3（若 syllables > 0），否则输出 0

### 复杂度分析
- 时间复杂度：O(|S|)，遍历一次字符串
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int vowels = 0, consonants = 0, y_count = 0, ng_count = 0;

    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == 'A' || S[i] == 'E' || S[i] == 'I' || S[i] == 'O' || S[i] == 'U') {
            vowels++;
        } else if (S[i] == 'Y') {
            y_count++;
        } else if (S[i] == 'N' && i + 1 < (int)S.size() && S[i + 1] == 'G') {
            ng_count++;
            i++;
        } else {
            consonants++;
        }
    }

    int total_consonants = consonants + ng_count;
    int total_vowels = vowels + y_count;

    int syllables = min(total_consonants / 2, total_vowels);

    if (syllables == 0) {
        cout << "0\n";
    } else {
        cout << syllables * 3 << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
给定字符串S，可以删除和重排字符形成"单词"。单词由音节组成，音节=辅音+元音+辅音。Y可作元音或辅音，NG可作为单个辅音。

### 核心思路
统计元音和辅音数量。Y可以补充到任意一边，NG算作一个辅音。每个音节需要2个辅音和1个元音，所以音节数=min(辅音数/2, 元音数)，答案=音节数×3。

### 算法流程
1. 统计元音(A,E,I,O,U)、Y、NG、其他辅音的数量
2. 总辅音=辅音数+NG数，总元音=元音数+Y数
3. 音节数=min(总辅音/2, 总元音)
4. 输出音节数×3

### 复杂度分析
- 时间复杂度：O(|S|)
- 空间复杂度：O(1)
