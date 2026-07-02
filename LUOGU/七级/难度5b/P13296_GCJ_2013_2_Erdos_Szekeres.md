# [GCJ 2013 #2] Erdős–Szekeres

## 题目描述

给定每个位置的 A[i]（以该位置为最大值的最长递增子序列长度）和 B[i]（以该位置为最大值的最长递减子序列长度），重建原排列。

## 输入格式

第一行 T，每组包含 N 和两行数组 A、B。

## 输出格式

Case #x: X[0] X[1] ... X[N-1]。

## 样例

```
2
1
1
1
8
1 2 1 3 3 1 4 1
4 4 3 4 3 2 2 1
```

输出：
```
Case #1: 1
Case #2: 4 5 3 7 6 2 8 1
```

## 解题思路

### 问题分析
关键性质：X[i] = |{j : A[j] ≤ A[i] 且 B[j] ≤ B[i]}|

### 核心思路
对于每个位置 i，统计有多少个位置 j 满足 A[j] ≤ A[i] 且 B[j] ≤ B[i]，该计数即为 X[i]。

### 算法流程
1. 对每个 i，遍历所有 j
2. 统计满足条件的 j 的数量
3. 输出结果

### 复杂度分析
- 时间：O(N²)
- 空间：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N; cin >> N;
        vector<int> A(N), B(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        for (int i = 0; i < N; i++) cin >> B[i];
        vector<int> X(N);
        for (int i = 0; i < N; i++) {
            int cnt = 0;
            for (int j = 0; j < N; j++)
                if (A[j] <= A[i] && B[j] <= B[i]) cnt++;
            X[i] = cnt;
        }
        cout << "Case #" << t << ":";
        for (int i = 0; i < N; i++) cout << " " << X[i];
        cout << "\n";
    }
    return 0;
}
```
