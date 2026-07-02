# [UOI 2023] An Array and Range Additions

## 题目描述

给定一个长度为 n 的数组 a。可以对任意子区间 [l,r] 加上任意整数 x。求使所有元素两两不同的最少操作次数。

## 输入格式

第一行 n。
第二行 n 个整数 a_1, a_2, ..., a_n。

## 输出格式

输出一个整数，表示最少操作次数。

## 样例

### 样例 1
输入：
```
3
1 2 3
```
输出：
```
0
```

### 样例 2
输入：
```
5
2 3 2 3 2
```
输出：
```
2
```

## 提示

- 1 ≤ n ≤ 2×10^5
- 1 ≤ a_i ≤ 10^9

## 解题思路

### 问题分析

每次操作可以对子区间加任意值。需要找到最少操作次数使数组元素两两不同。

### 核心思路

1. 统计重复元素的频率
2. 每次操作可以处理一个连续子数组
3. 最优策略需要考虑重复元素的位置分布

### 算法流程

1. 统计每个值的出现次数
2. 找到最大频率 max_freq
3. 最少操作次数至少为 max_freq - 1

### 复杂度分析

- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

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
    
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    bool all_different = true;
    for (int i = 1; i < n; i++) {
        if (sorted_a[i] == sorted_a[i - 1]) {
            all_different = false;
            break;
        }
    }
    
    if (all_different) {
        cout << 0 << endl;
        return 0;
    }
    
    vector<int> freq(100001, 0);
    int max_freq = 0;
    for (int x : a) {
        freq[x]++;
        max_freq = max(max_freq, freq[x]);
    }
    
    cout << max_freq - 1 << endl;
    return 0;
}
```
