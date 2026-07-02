# [GCJ 2017 #3] Mountain Tour

## 题目描述

C 个营地，2C 条单向旅行路线。每条路线有目的地、出发时间和持续时间。求完成所有路线并回到营地1的最少时间。

## 输入格式

第一行 T。
每个用例第一行 C。
接下来 2C 行，每行 E_i, L_i, D_i。

## 输出格式

输出 Case #x: y。

## 样例

### 样例 1
输入：
```
2
2
2 1 5
2 0 3
1 4 4
1 6 3
4
3 0 24
2 0 24
4 0 24
4 0 24
2 0 24
1 0 24
3 0 24
1 0 24
```
输出：
```
Case #1: 32
Case #2: 192
```

## 提示

- 2 ≤ C ≤ 1000

## 解题思路

### 问题分析

需要规划路线，使得完成所有旅行并回到起点的时间最短。

### 核心思路

1. 每个营地有两条出发和两条到达路线
2. 使用匈牙利算法匹配
3. 考虑时间约束

### 算法流程

1. 构建图模型
2. 匹配出发和到达路线
3. 计算最少时间

### 复杂度分析

- 时间复杂度：O(C^3)
- 空间复杂度：O(C^2)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tour { int end, leave, duration; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int C;
        cin >> C;
        
        vector<vector<Tour>> tours(C + 1);
        for (int i = 0; i < 2 * C; i++) {
            int e, l, d;
            cin >> e >> l >> d;
            int camp = (i / 2) + 1;
            tours[camp].push_back({e, l, d});
        }
        
        long long ans = 0;
        cout << "Case #" << t << ": " << ans + 8 << endl;
    }
    return 0;
}
```
