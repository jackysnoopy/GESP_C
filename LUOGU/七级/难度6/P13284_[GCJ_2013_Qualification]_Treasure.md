# [GCJ 2013 Qualification] Treasure

## 题目描述

有 N 个宝箱，每个需要特定钥匙打开，打开后可能获得新钥匙。求打开所有宝箱的顺序。

## 输入格式

第一行 T。
每个用例第一行 K, N。
第二行 K 个初始钥匙。
接下来 N 行描述宝箱。

## 输出格式

输出 Case #x: 顺序或 IMPOSSIBLE。

## 样例

### 样例 1
输入：
```
3
1 4
1
1 0
1 2 1 3
2 0
3 1 2
3 3
1 1 1
1 0
1 0
1 0
1 1
2
1 1 1
```
输出：
```
Case #1: 2 1 4 3
Case #2: 1 2 3
Case #3: IMPOSSIBLE
```

## 提示

- 1 ≤ N ≤ 200

## 解题思路

### 问题分析

需要找到打开宝箱的顺序，使得能打开所有宝箱。

### 核心思路

1. 贪心选择能打开的最小编号宝箱
2. 收集获得的钥匙
3. 继续打开下一个

### 算法流程

1. 维护当前拥有的钥匙
2. 每次选择能打开的最小编号宝箱
3. 打开后更新钥匙集合

### 复杂度分析

- 时间复杂度：O(N^2)
- 空间复杂度：O(N + K)

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
        int K, N;
        cin >> K >> N;
        
        vector<int> keys(K);
        for (int i = 0; i < K; i++) cin >> keys[i];
        
        vector<int> chest_type(N);
        vector<vector<int>> chest_keys(N);
        
        for (int i = 0; i < N; i++) {
            int T_i, K_i;
            cin >> T_i >> K_i;
            chest_type[i] = T_i;
            chest_keys[i].resize(K_i);
            for (int j = 0; j < K_i; j++) cin >> chest_keys[i][j];
        }
        
        vector<bool> opened(N, false);
        vector<int> order;
        vector<int> have = keys;
        
        for (int step = 0; step < N; step++) {
            int best = -1;
            for (int i = 0; i < N; i++) {
                if (!opened[i]) {
                    bool can_open = false;
                    for (int k : have) {
                        if (k == chest_type[i]) { can_open = true; break; }
                    }
                    if (can_open && (best == -1 || i < best)) best = i;
                }
            }
            
            if (best == -1) { order.clear(); break; }
            
            opened[best] = true;
            order.push_back(best + 1);
            
            for (int j = 0; j < have.size(); j++) {
                if (have[j] == chest_type[best]) {
                    have.erase(have.begin() + j);
                    break;
                }
            }
            for (int k : chest_keys[best]) have.push_back(k);
        }
        
        if (order.empty()) cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        else {
            cout << "Case #" << t << ":";
            for (int i = 0; i < N; i++) cout << " " << order[i];
            cout << endl;
        }
    }
    return 0;
}
```
