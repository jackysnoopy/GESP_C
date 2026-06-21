# [GKS 2019 #B] Energy Stones

## 题目描述

Duda the rock monster lives in the enchanted forest and has collected $N$ energy stones for lunch. Since he has a small mouth, he eats energy stones one at a time. Some stones are tougher than others! The $i$-th stone takes him $S_i$ seconds to eat.

Duda eats energy stones to get **energy**. Different stones give him different amounts of energy. Furthermore, the stones lose energy over time. The $i$-th stone initially contains $E_i$ units of energy and will lose $L_i$ units of energy each second. When Duda starts to eat a stone, he will receive all the energy the stone contains immediately (no matter how much time it takes to actually finish eating the stone). The stone's energy stops decreasing once it hits zero.

What is the largest amount of energy Duda could receive from eating his stones?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing the integer $N$, the number of energy stones Duda has. Then, there are $N$ more lines, the $i$-th of which contains the three integers $S_i$, $E_i$ and $L_i$, as described above.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum amount of energy Duda could receive from eating stones.

## 样例

### 样例输入 1
```
2
3
10 4 1000
10 3 1000
10 8 1000
2
10 2 0
10 3 0
```

### 样例输出 1
```
Case #1: 8
Case #2: 5
```

### 样例输入 2
```
2
4
20 10 1
5 30 5
100 30 1
5 80 60
2
12 300 50
5 200 0
```

### 样例输出 2
```
Case #1: 105
Case #2: 500
```

## 提示

### Sample

In Sample Case #1, there are $N = 3$ stones. No matter which stone Duda eats, the other two will have no energy left once he is done eating. So he should eat the third stone, giving him $8$ units of energy.

### Additional Sample - Test Set 2

The following additional sample fits the limits of Test Set 2. It will not be run against your submitted solutions.

In Sample Case #1, there are $N = 4$ stones. One possible order Duda can eat stones is:

- Eat the fourth stone. This takes $5$ seconds and gives him $80$ units of energy.
- Eat the second stone. This takes $5$ more seconds and gives him $5$ units of energy (the second stone started with $30$ energy, and over $5$ seconds, has lost $25$ units of energy).
- Eat the third stone. This takes $100$ more seconds and gives him $20$ units of energy (the third stone started with $30$ energy, and over $10$ seconds, has lost $10$ units of energy).
- Eat the first stone. This takes $20$ more seconds and gives him $0$ units of energy (the first stone started with $10$ units of energy, and over $110$ seconds, has lost all of its energy).

This gives him $105$ units of energy, which is the best he can do. So the answer is $105$.

In Sample Case #2, there are $N = 2$ stones. Duda can:

- Eat the first stone. This takes $12$ seconds and gives him $300$ units of energy.
- Eat the second stone. This takes $5$ seconds and gives him $200$ units of energy (the second stone does not lose any energy over time!).

So the answer is $500$.

### Limits

$1 \le T \le 100$.

$1 \le N \le 100$.

$1 \le S_i \le 100$.

$1 \le E_i \le 10^5$.

$0 \le L_i \le 10^5$.

**Test set 1 (Visible)**

All stones take the same amount of time to eat. That is: $S_i = S_j$ for all $i$ and $j$.

**Test set 2 (Hidden)**

There are no additional constraints beyond the general Limits.

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

        vector<int> S(N), E(N), L(N);
        for (int i = 0; i < N; i++) cin >> S[i] >> E[i] >> L[i];

        long long ans = 0;
        for (int i = 0; i < N; i++) {
            ans += max(0, E[i]);
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```
