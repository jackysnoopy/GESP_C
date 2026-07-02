# [ICPC 2018 Yokohama R] Sixth Sense

## 题目描述

Ms. Future is gifted with precognition. Naturally, she is excellent at some card games since she can correctly foresee every player's actions, except her own. Today, she accepted a challenge from a reckless gambler Mr. Past. They agreed to play a simple two-player trick-taking card game.

Cards for the game have a number printed on one side, leaving the other side blank making indistinguishable from other cards.

A game starts with the same number, say $n$, of cards being handed out to both players, without revealing the printed number to the opponent.

A game consists of $n$ tricks. In each trick, both players pull one card out of her/his hand. The player pulling out the card with the larger number takes this trick. Because Ms. Future is extremely good at this game, they have agreed to give tricks to Mr. Past when both pull out cards with the same number. Once a card is used, it can never be used later in the same game. The game continues until all the cards in the hands are used up. The objective of the game is to take as many tricks as possible.

Your mission of this problem is to help Ms. Future by providing a computer program to determine the best playing order of the cards in her hand. Since she has the sixth sense, your program can utilize information that is not available to ordinary people before the game.

## 输入格式

The input consists of a single test case of the following format.

$$
\begin{aligned}
& n \\
& p_1 \; \cdots \; p_n \\
& f_1 \; \cdots \; f_n
\end{aligned}
$$

$n$ in the first line is the number of tricks, which is an integer between $2$ and $5000$, inclusive. The second line represents the Mr. Past's playing order of the cards in his hand. In the $i$-th trick, he will pull out a card with the number $p_i$ ($1 \leq i \leq n$). The third line represents the Ms. Future's hand. $f_i$ ($1 \leq i \leq n$) is the number that she will see on the $i$-th received card from the dealer. Every number in the second or third line is an integer between $1$ and $10\,000$, inclusive. These lines may have duplicate numbers.

## 输出格式

The output should be a single line containing $n$ integers $a_1 \; \cdots \; a_n$ separated by a space, where $a_i$ ($1 \leq i \leq n$) is the number on the card she should play at the $i$-th trick for maximizing the number of taken tricks. If there are two or more such sequences of numbers, output the lexicographically greatest one among them.

## 样例

### 样例 1
**输入：**
```
5
1 2 3 4 5
1 2 3 4 5
```
**输出：**
```
2 3 4 5 1
```

### 样例 2
**输入：**
```
5
3 4 5 6 7
1 3 5 7 9
```
**输出：**
```
9 5 7 3 1
```

### 样例 3
**输入：**
```
5
3 2 2 1 1
1 1 2 2 3
```
**输出：**
```
1 3 1 2 2
```

### 样例 4
**输入：**
```
5
3 4 10 4 9
2 7 3 6 9
```
**输出：**
```
9 7 3 6 2
```

## 提示

（无）

## 解题思路

### 问题分析

本题要求在卡牌游戏中找到最优的出牌顺序，使得赢得的回合数最多。

### 核心思路

使用贪心算法：
1. 对于对手的每张牌，找到能刚好打赢它的最小牌
2. 如果没有能打赢的牌，就出最小的牌
3. 这样可以最大化赢得的回合数

### 算法流程

1. 读取对手的出牌顺序和自己的手牌
2. 对于对手的每张牌：
   - 找到能刚好打赢它的最小牌
   - 如果没有，就出最小的牌
3. 输出出牌顺序

### 复杂度分析

- 时间复杂度：$O(n \log n)$，其中n是牌的数量
- 空间复杂度：$O(n)$，用于存储手牌

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    
    multiset<int> cards(f.begin(), f.end());
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        auto it = cards.upper_bound(p[i]);
        if (it != cards.end()) {
            result.push_back(*it);
            cards.erase(it);
        } else {
            result.push_back(*cards.begin());
            cards.erase(cards.begin());
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    
    return 0;
}
```