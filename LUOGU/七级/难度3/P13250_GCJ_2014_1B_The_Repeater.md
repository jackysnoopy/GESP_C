# [GCJ 2014 #1B] The Repeater

## 题目描述

Fegla and Omar like to play games every day. But now they are bored of all games, and they would like to play a new game. So they decided to invent their own game called "The Repeater".

They invented a $2$ player game. Fegla writes down $N$ strings. Omar's task is to make all the strings identical, if possible, using the minimum number of actions (possibly $0$ actions) of the following two types:

- Select any character in any of the strings and repeat it (add another instance of this character exactly after it). For example, in a single move Omar can change "abc" to "abbc" (by repeating the character 'b').
- Select any two adjacent and identical characters in any of the strings, and delete one of them. For example, in a single move Omar can change "abbc" to "abc" (delete one of the 'b' characters), but can't convert it to "bbc".

The $2$ actions are independent; it's not necessary that an action of the first type should be followed by an action of the second type (or vice versa).

Help Omar to win this game by writing a program to find if it is possible to make the given strings identical, and to find the minimum number of moves if it is possible.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing an integer $N$ which is the number of strings. Followed by $N$ lines, each line contains a non-empty string (each string will consist of lower case English characters only, from 'a' to 'z').

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is the minimum number of moves to make the strings identical. If there is no possible way to make all strings identical, print "Fegla Won" (quotes for clarity).

## 样例

### 样例输入 1
```
5
2
mmaw
maw
2
gcj
cj
3
aaabbb
ab
aabb
2
abc
abc
3
aabc
abbc
abcc
```

### 样例输出 1
```
Case #1: 1
Case #2: Fegla Won
Case #3: 4
Case #4: 0
Case #5: 3
```

## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq \text{length of each string} \leq 100$.

**Small dataset(10 Pts)**

- Time limit: $60$ seconds.
- $N = 2$.

**Large dataset(13 Pts)**

- Time limit: $120$ seconds.
- $2 \leq N \leq 100$.

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
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<pair<char,int>> rle(const string& s) {
    vector<pair<char,int>> r;
    for (char c : s) {
        if (r.empty() || r.back().first != c) r.push_back({c, 1});
        else r.back().second++;
    }
    return r;
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<string> s(N);
        for (int i = 0; i < N; i++) cin >> s[i];
        vector<vector<pair<char,int>>> enc(N);
        for (int i = 0; i < N; i++) enc[i] = rle(s[i]);
        bool ok = true;
        int len = enc[0].size();
        for (int i = 1; i < N; i++)
            if ((int)enc[i].size() != len) ok = false;
        if (ok) {
            for (int j = 0; j < len; j++)
                for (int i = 1; i < N; i++)
                    if (enc[i][j].first != enc[0][j].first) ok = false;
        }
        cout << "Case #" << tc << ": ";
        if (!ok) { cout << "Fegla Won\n"; continue; }
        int ans = 0;
        for (int j = 0; j < len; j++) {
            vector<int> cnts;
            for (int i = 0; i < N; i++) cnts.push_back(enc[i][j].second);
            sort(cnts.begin(), cnts.end());
            int med = cnts[N / 2];
            for (int v : cnts) ans += abs(v - med);
        }
        cout << ans << "\n";
    }
    return 0;
}
```