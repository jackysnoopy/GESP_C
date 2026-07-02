# [GCJ 2020 #3] Thermometers

## 题目描述

海岸线是周长为 K 的圆。温度计放置在某些点，未放置点使用最近温度计的温度。求最少温度计数量。

## 输入格式

第一行 T。
每个用例第一行 K, N。
第二行 N 个整数 X_i。
第三行 N 个整数 T_i。

## 输出格式

输出 Case #x: y。

## 样例

### 样例 1
输入：
```
3
2 2
0 1
184 330
3 2
0 1
184 330
10 3
1 5 9
184 200 330
```
输出：
```
Case #1: 2
Case #2: 3
Case #3: 3
```

## 提示

- 2 ≤ K ≤ 10^9
- 2 ≤ N ≤ 100

## 解题思路

### 问题分析

需要找到最少温度计数量，使得产生的温度数据与给定数据一致。

### 核心思路

1. 统计不同温度的数量
2. 每个温度变化点需要至少一个温度计
3. 贪心放置温度计

### 算法流程

1. 计算相邻温度变化点的距离
2. 统计不同温度数量
3. 输出最少温度计数

### 复杂度分析

- 时间复杂度：O(N)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        long long K;
        int N;
        cin >> K >> N;
        
        vector<long long> X(N), T(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        for (int i = 0; i < N; i++) cin >> T[i];
        
        int diff_temp = 1;
        for (int i = 1; i < N; i++) {
            if (T[i] != T[i - 1]) diff_temp++;
        }
        
        cout << "Case #" << t << ": " << max(diff_temp, 2) << endl;
    }
    return 0;
}
```
