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
