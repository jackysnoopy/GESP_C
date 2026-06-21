# [ZJCPC 2017] Heap Partition

## 题目描述

A sequence $S=\{s_1,s_2,\dots,s_n\}$ is called $\textit{heapable}$ if there exists a binary tree $T$ with $n$ nodes such that every node is labelled with exactly one element from the sequence $S$, and for every non-root node $s_i$ and its parent $s_j$, $s_j \le s_i$ and $j < i$ hold. Each element in sequence $S$ can be used to label a node in tree $T$ only once.

Chiaki has a sequence $a_1,a_2,\dots,a_n$, she would like to decompose it into a minimum number of heapable subsequences.

Note that a subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

## 输入格式

There are multiple test cases. The first line of input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contain an integer $n$ ($1 \le n \le 10^5$) -- the length of the sequence.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le n$).

It is guaranteed that the sum of all $n$ does not exceed $2 \times 10^6$.

## 输出格式

For each test case, output an integer $m$ denoting the minimum number of heapable subsequences in the first line. For the next $m$ lines, first output an integer $C_i$, indicating the length of the subsequence. Then output $C_i$ integers $P_{i1}, P_{i2}, \dots, P_{iC{_i}}$ in increasing order on the same line, where $P_{ij}$ means the index of the $j$-th element of the $i$-th subsequence in the original sequence.

## 样例

### 样例输入 1
```
4
4
1 2 3 4
4
2 4 3 1
4
1 1 1 1
5
3 2 1 4 1
```

### 样例输出 1
```
1
4 1 2 3 4
2
3 1 2 3
1 4
1
4 1 2 3 4
3
2 1 4
1 2
2 3 5
```

## 提示

难度：普及+/提高

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

    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> tails;
        vector<int> pos(n, -1);

        for (int i = 0; i < n; i++) {
            auto it = upper_bound(tails.begin(), tails.end(), a[i]);
            int idx = it - tails.begin();
            if (it == tails.end()) {
                tails.push_back(a[i]);
            } else {
                *it = a[i];
            }
            pos[i] = idx;
        }

        int m = tails.size();
        cout << m << "\n";

        vector<vector<int>> subsequences(m);
        for (int i = n - 1; i >= 0; i--) {
            subsequences[pos[i]].push_back(i + 1);
        }

        for (int i = 0; i < m; i++) {
            sort(subsequences[i].begin(), subsequences[i].end());
            cout << subsequences[i].size();
            for (int x : subsequences[i]) cout << " " << x;
            cout << "\n";
        }
    }

    return 0;
}
```
