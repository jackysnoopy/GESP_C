# [GCJ 2014 Finals] Paradox Sort

## 题目描述

Vlad 喜欢糖果。给定 N 个糖果和偏好关系，找出一种排列使得 Vlad 最终得到指定的糖果 A。

## 输入格式

第一行 T。
每个用例第一行 N, A。
接下来 N 行是偏好矩阵。

## 输出格式

输出 Case #x: 排列或 IMPOSSIBLE。

## 样例

### 样例 1
输入：
```
3
2 0
-Y
N-
2 0
-N
Y-
4 3
-YNN
N-YY
YN-Y
YNN-
```
输出：
```
Case #1: 0 1
Case #2: IMPOSSIBLE
Case #3: 1 2 0 3
```

## 提示

- 1 ≤ N ≤ 100

## 解题思路

### 问题分析

需要找到排列使得 Vlad 最终选择指定糖果。

### 核心思路

1. 贪心构建排列
2. 检查偏好关系
3. 验证最终结果

### 算法流程

1. 从目标糖果开始
2. 逐步添加其他糖果
3. 检查是否可行

### 复杂度分析

- 时间复杂度：O(N^3)
- 空间复杂度：O(N^2)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, A;
        cin >> N >> A;
        
        vector<string> pref(N);
        for (int i = 0; i < N; i++) cin >> pref[i];
        
        vector<int> order;
        vector<bool> used(N, false);
        
        order.push_back(A);
        used[A] = true;
        
        for (int step = 1; step < N; step++) {
            int best = -1;
            for (int i = 0; i < N; i++) {
                if (!used[i]) {
                    bool ok = true;
                    for (int j = 0; j < order.size(); j++) {
                        if (pref[i][order[j]] == 'N') { ok = false; break; }
                    }
                    if (ok && (best == -1 || i < best)) best = i;
                }
            }
            if (best != -1) {
                order.insert(order.begin(), best);
                used[best] = true;
            }
        }
        
        if (order.size() == N) {
            cout << "Case #" << t << ":";
            for (int i = 0; i < N; i++) cout << " " << order[i];
            cout << endl;
        } else {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        }
    }
    return 0;
}
```
