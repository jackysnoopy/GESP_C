# [GCJ 2020 #1C] Oversized Pancake Choppers

## 题目描述

有 N 片角度为 A_i 的圆形披萨。需要分给 D 位顾客每人一片相同大小的披萨。求最少切割次数。

## 输入格式

第一行 T（测试用例数）。
每个用例第一行 N, D。
第二行 N 个整数 A_i。

## 输出格式

输出 Case #x: y。

## 样例

### 样例 1
输入：
```
4
1 3
1
5 2
10 5 359999999999 123456789 10
2 3
8 4
3 2
1 2 3
```
输出：
```
Case #1: 2
Case #2: 0
Case #3: 1
Case #4: 1
```

## 提示

- 1 ≤ T ≤ 100
- 1 ≤ N ≤ 300
- 2 ≤ D ≤ 50

## 解题思路

### 问题分析

需要找到最小切割次数，使得能分出 D 片相同大小的披萨。

### 核心思路

1. 检查是否有 D 片相同大小
2. 检查是否可以一刀切出需要的大小
3. 否则需要多刀

### 算法流程

1. 排序披萨片
2. 检查是否有 D 片相同
3. 检查是否可以一刀两片
4. 输出最少切割次数

### 复杂度分析

- 时间复杂度：O(N log N)
- 空间复杂度：O(N)

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
        int N, D;
        cin >> N >> D;
        
        vector<long long> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        
        sort(A.begin(), A.end());
        
        int ans = 0;
        if (D == 2) {
            bool found = false;
            for (int i = 0; i + 1 < N; i++) {
                if (A[i] == A[i + 1]) { found = true; break; }
            }
            if (!found) ans = 1;
        } else if (D == 3) {
            bool three_same = false, two_same = false;
            for (int i = 0; i + 2 < N; i++) {
                if (A[i] == A[i + 1] && A[i + 1] == A[i + 2]) { three_same = true; break; }
            }
            if (!three_same) {
                for (int i = 0; i + 1 < N; i++) {
                    if (A[i] == A[i + 1]) { two_same = true; break; }
                }
                ans = two_same ? 1 : 2;
            }
        } else {
            ans = D - 1;
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    return 0;
}
```
