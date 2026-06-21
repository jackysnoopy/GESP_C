# [ICPC 2018 Jakarta R] Lexical Sign Sequence

## 题目描述

Andi likes numbers and sequences, especially, sign sequences. A sign sequence is a sequence which consists of $-1$ and $1$. Andi is a curious person, thus, he wants to build a sign sequence which length is $N$ (the positions are numbered from $1$ to $N$, inclusive).

However, Andi also likes some challenges. Therefore, he prefilled some positions in the sequence with $-1$ or $1$ (the number in these positions cannot be changed). Andi also wants the sequence to fulfill $K$ constraints. For each constraint, there are 3 numbers: $A_i$, $B_i$, and $C_i$. This means that the sum of numbers which position is in the range $[A_i, B_i]$ (inclusive) must be at least $C_i$.

Sounds confusing, right? It is not done yet. Since there can be many sequences that fulfill all the criteria above, Andi wants the sequence to be lexicographically smallest. Sequence $X$ is lexicographically smaller than sequence $Y$ if and only if there exists a position $i$ where $X_i < Y_i$ and $X_j = Y_j$ for all $j < i$.

Find the sequence Andi wants.

## 输入格式

Input begins with a line containing two integers: $N$ $K$ ($1 \leq N \leq 100000$; $0 \leq K \leq 100000$) representing the length of the sequence and the number of constraints, respectively. The second line contains $N$ integers: $P_i$ ($-1 \leq P_i \leq 1$). If $P_i = 0$, then the $i^{th}$ position in the sequence is not prefilled, otherwise the $i^{th}$ position in the sequence is prefilled by $P_i$. The next $K$ lines, each contains three integers: $A_i$ $B_i$ $C_i$ ($1 \leq A_i \leq B_i \leq N$; $-N \leq C_i \leq N$) representing the $i^{th}$ constraint.

## 输出格式

Output contains $N$ integers (each separated by a single space) in a line representing the sequence that Andi wants if there exists such sequence, or “Impossible” (without quotes) otherwise.

## 样例

### 样例输入 1
```
3 2
0 0 0
1 2 2
2 3 -1
```

### 样例输出 1
```
1 1 -1
```

### 样例输入 2
```
3 2
0 -1 0
1 2 2
2 3 -1
```

### 样例输出 2
```
Impossible
```

## 提示

**Explanation for the sample input/output #1**

Both sequences $[1, 1, -1]$ and $[1, 1, 1]$ satisfy the prefilled conditions and the given $K$ constraints. The former is lexicographically smaller.

**Explanation for the sample input/output #2**

The second position is already prefilled with $-1$, so it is impossible to fulfill the first constraint. There is no valid sequence in this case.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    vector<int> result(N, 0);
    for (int i = 0; i < N; i++) {
        if (P[i] != 0) result[i] = P[i];
    }

    vector<pair<int, int>> constraints(K);
    for (int i = 0; i < K; i++) {
        cin >> constraints[i].first >> constraints[i].second;
    }

    for (int i = 0; i < N; i++) {
        if (P[i] == 0) {
            result[i] = -1;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << result[i];
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
```
