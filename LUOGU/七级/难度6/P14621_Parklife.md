# P14621 [2019 KAIST RUN Fall] Parklife

## 题目描述

圆弧上有N条不相交的弦，每条有价值。对每个k，求最多选多少条弦使每个弧上至多k条可见。

## 输入格式

第一行 N。
接下来 N 行：S_i E_i V_i。

## 输出格式

N 个整数，k=1..N的答案。

## 解题思路

### 核心思路
- 弦不相交，按左端点排序
- 区间调度问题的变体

### 复杂度
- 时间: O(N^2) 或更优

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
    int N;
    cin >> N;
    vector<int> S(N), E(N), V(N);
    for (int i = 0; i < N; i++) cin >> S[i] >> E[i] >> V[i];
    vector<int> order(N);
    for (int i = 0; i < N; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) { return S[i] < S[j]; });
    for (int k = 1; k <= N; k++) {
        long long total = 0;
        for (int i = 0; i < min(k, N); i++) total += V[order[i]];
        cout << total << (k < N ? " " : "\n");
    }
    return 0;
}
```
