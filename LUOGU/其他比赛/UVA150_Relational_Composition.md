# UVA150 - Relational Composition (关系组合)

## 题目描述

给定一个集合 {1..n} 上的两个二元关系 R 和 S，计算它们的组合 T = R∘S，其中 (i,k)∈T 当且仅当存在 j 使得 (i,j)∈S 且 (j,k)∈R。

输入格式：空行，然后 n，接着关系 R 的条目（以 0 0 结束），然后关系 S 的条目。输出格式：空行，然后 T 的条目，最后空行。n<=20。

## 解题思路

### 问题分析

这是一个关系组合问题。给定两个二元关系 R 和 S，需要计算它们的组合关系 T。

### 核心思路

关系组合的定义：T = R∘S，其中 (i,k)∈T 当且仅当存在 j 使得 (i,j)∈S 且 (j,k)∈R。

这本质上是一个矩阵乘法问题，只是将乘法替换为逻辑与，加法替换为逻辑或。

### 算法流程

1. 读取 n
2. 读取关系 R，用布尔矩阵表示
3. 读取关系 S，用布尔矩阵表示
4. 计算关系组合 T
5. 输出结果

### 复杂度分析

- 时间复杂度：O(n^3)
- 空间复杂度：O(n^2)

## 代码实现

```cpp
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        int n = stoi(line);
        vector<vector<bool>> R(n + 1, vector<bool>(n + 1, false));
        vector<vector<bool>> S(n + 1, vector<bool>(n + 1, false));

        int i, j;
        while (cin >> i >> j && (i != 0 || j != 0)) {
            R[i][j] = true;
        }
        while (cin >> i >> j && (i != 0 || j != 0)) {
            S[i][j] = true;
        }
        cin.ignore();

        vector<vector<bool>> T(n + 1, vector<bool>(n + 1, false));
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (S[a][b]) {
                    for (int c = 1; c <= n; ++c) {
                        if (R[b][c]) {
                            T[a][c] = true;
                        }
                    }
                }
            }
        }

        cout << "\n";
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (T[a][b]) {
                    cout << a << " " << b << "\n";
                }
            }
        }
        cout << "\n";
    }

    return 0;
}
```
