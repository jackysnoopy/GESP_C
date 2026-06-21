# [USACO26FEB] Swap to Win B

## 题目描述

Farmer John has a favorite string $t$ with $M$ characters. He also has $N$ strings $s_1, s_2, \ldots, s_N$ each with $M$ characters ($1 \leq N, M \leq 1000$).

FJ can perform the following two types of operations:

- FJ chooses any string $s_x$ and two indices $p$ and $q$. Then, he swaps the $p$'th and $q$'th character of $s_x$ ($1\le x\le N, 1\le p,q\le M$).
- FJ chooses two strings $s_x$ and $s_y$ and an index $k$. Then, he swaps the $k$'th characters of $s_x$ and $s_y$ ($1\le x,y\le N, 1\le k\le M$).

His goal is to make $s_1$ equal to $t$. Find any series of operations that fulfills his goal. Because FJ is in a hurry, he only has time to perform a total of $2M$ operations. The inputs guarantee that it is possible to fulfill FJ's goal.

## 输入格式

The first line contains $T$ ($1\le T\le 10$), the number of independent tests. Each test is specified in the following format:

The first line contains $N$ and $M$.

The second line contains $t$.

Then, $N$ lines follow, the $i$'th of which contains $s_i$.

The inputs will guarantee that it is possible to fulfill FJ's goal. All strings contain lowercase English letters (a-z).

## 输出格式

The output for each test should be as follows:
On the first line, output an integer $K$, the number of operations you will perform. $K$ must be a non-negative integer less than or equal to $2M$.

Then, output $K$ lines, denoting the operations you will perform in sequential order. Each line should be one of the following:

- $\texttt{1 x p q}$
- $\texttt{2 x y k}$

## 样例

### 样例输入 1
```
3
3 6
banana
nabana
banana
nnbaaa
5 3
abc
def
bca
ghi
jkl
mno
3 5
abcde
abcde
abcde
zzzzz
```

### 样例输出 1
```
3
2 1 2 1
1 1 3 5
2 1 2 5
5
1 2 1 3
2 1 2 1
1 2 2 3
2 1 2 2
2 1 2 3
0
```

## 提示

Here is how $s$ changes according to the first test's output (with letters swapped in uppercase):

```
nabana    Babana    baNaBa    banaNa
banana -> Nanana -> nanana -> nanaBa
nnbaaa    nnbaaa    nnbaaa    nnbaaa
```

After all three operations, $s_1=t$.

### SCORING:
- Inputs 2-6: $N, M \le 100$
- Inputs 7-12: No additional constraints.

Problem credits: Chongtian Ma

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int x, int y) { return a[x] < a[y]; });

    vector<bool> vis(n, false);
    int cycles = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i] || idx[i] == i) continue;
        int j = i;
        while (!vis[j]) {
            vis[j] = true;
            j = idx[j];
        }
        cycles++;
    }

    cout << n - cycles << "\n";
    return 0;
}
```
