# [ICPC 2020 Shanghai R] Rice Arrangement

## 题目描述

n 个椅子均匀分布在一个圆桌上，k 个客人坐在 k 个不同椅子上，k 碗饭放在 k 个不同位置。可以旋转桌子（每次转 2π/n 度），使碗移到客人面前。每次旋转后客人可以取走面前的碗。求最小旋转次数使每人取到一碗。

## 输入格式

第一行两个整数 n, k。  
第二行 k 个整数，表示客人的位置（0-indexed）。  
第三行 k 个整数，表示碗的位置（0-indexed）。

## 输出格式

一个整数，表示最小旋转次数。

## 样例

### 样例 1

**输入：**
```
4 2
0 2
1 3
```

**输出：**
```
2
```

## 提示

- 1 ≤ n ≤ 10^9
- 1 ≤ k ≤ min(n, 1000)
- 所有测试的 k 之和 ≤ 5000

## 解题思路

### 问题分析

圆桌上有 n 个位置，k 个客人和 k 碗饭。旋转桌子使碗移到客人面前，每次旋转 1 个位置。需要找到最优的旋转策略，使所有客人都能取到一碗。

### 核心思路

**枚举旋转偏移 + 贪心匹配**：

1. **枚举旋转偏移 d**：对于每对 (客人 g, 碗 b)，尝试旋转偏移 d = (g - b) mod n，使碗 b 对齐客人 g。
2. **贪心匹配**：对每个偏移 d，将所有碗位置平移 d 后排序，与排序后的客人位置一一匹配。
3. **计算代价**：旋转次数 = 匹配中位置差的绝对值之和（圆上距离）。

### 算法流程

1. 排序客人位置和碗位置。
2. 枚举所有 k² 种旋转偏移 d = (g_i - b_j) mod n。
3. 对每个 d，平移所有碗位置，排序后与客人贪心匹配。
4. 计算匹配代价，取最小值。

### 复杂度分析

- 时间：O(k³ log k)，枚举 k² 种偏移，每次排序 O(k log k)。
- 空间：O(k)。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> guests(k), bowls(k);
    for (int i = 0; i < k; i++) cin >> guests[i];
    for (int i = 0; i < k; i++) cin >> bowls[i];

    sort(guests.begin(), guests.end());
    sort(bowls.begin(), bowls.end());

    long long ans = LLONG_MAX;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            int d = ((guests[i] - bowls[j]) % n + n) % n;

            vector<int> shifted(k);
            for (int l = 0; l < k; l++) {
                shifted[l] = (bowls[l] + d) % n;
            }
            sort(shifted.begin(), shifted.end());

            long long cost = 0;
            for (int l = 0; l < k; l++) {
                int diff = abs(guests[l] - shifted[l]);
                cost += min(diff, n - diff);
            }

            ans = min(ans, cost);
        }
    }

    cout << ans << endl;
    return 0;
}
```
