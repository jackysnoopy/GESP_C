# P13385 [GCJ 2011 Finals] Ace in the Hole

## 题目描述

Amy has a deck of $N$ cards with values $1$ through $N$. She arranges the deck so that the values of the cards have no decreasing subsequence of length $3$.

Ben knows that the deck has no decreasing subsequence of length $3$, but he does not know the exact ordering. He wants to find the card with value $1$. He does this by choosing an arbitrary card, picking it up to observe its value, and then repeating until he has found the card with value $1$.

Ben later tells you that he got unlucky and had to examine all $N$ cards before finding the card with value $1$. Given the order in which he examined the cards of the deck, what value did each card have?

## 输入格式

第一行输入测试用例数量 $T$。每组测试用例以一行包含一个整数 $N$ 开始，然后是一行包含 $N$ 个整数，描述Ben检查卡牌的顺序。

## 输出格式

对于每个测试用例，输出一行包含 `Case #$x$: $y$`，其中 $y$ 是卡牌值的序列。

## 样例

### 样例1
输入：
```
1
3
2 1 3
```
输出：
```
Case #1: 2 3 1
```

## 提示

$1 \leq T \leq 100$。

## 解题思路

### 问题分析

这是一个推理问题。需要根据检查顺序推断卡牌值。

### 核心思路

**贪心推断**：从最后一个检查的卡牌开始，分配最大的未使用值。

### 算法流程

```
对于每个测试用例:
    从最后一个检查的卡牌开始
    分配最大的未使用值
    输出结果
```

### 复杂度分析

- **时间复杂度**：$O(N^2)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        vector<int> order(N);
        for (int i = 0; i < N; i++) {
            cin >> order[i];
            order[i]--;
        }
        
        vector<int> values(N);
        vector<bool> used(N, false);
        
        for (int i = N - 1; i >= 0; i--) {
            int pos = order[i];
            
            for (int v = N - 1; v >= 0; v--) {
                if (!used[v]) {
                    values[pos] = v + 1;
                    used[v] = true;
                    break;
                }
            }
        }
        
        cout << "Case #" << t << ":";
        for (int i = 0; i < N; i++) {
            cout << " " << values[i];
        }
        cout << "\n";
    }
    
    return 0;
}
```
