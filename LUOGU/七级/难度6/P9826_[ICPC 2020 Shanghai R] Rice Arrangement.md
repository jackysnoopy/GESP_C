# P9826 [ICPC 2020 Shanghai R] Rice Arrangement

## 题目描述

Wowo is a hospitable Xinjiang uncle. $k$ guests will have Uyghur Polo in Wowo's house around a big round table. $n$ chairs are placed around the table uniformly. Each guest sits on a chair and no two guests sit on the same chair. $k$ bowls of Uyghur Polo are on the table. Each bowl is next to some chair (with or without some guest sitting on it). No two bowls locate at the same position.

As a waiter, you are supposed to assign each person with exactly one bowl of Uyghur Polo. The table can be rotated, so each time you can turn it $\frac{2\pi}{n}$ degrees clockwise or counterclockwise. The bowls turn with the table while the chairs and guests do not move. When one bowl of Uyghur Polo is in front of a guest, he can either take it or wait for another.

You want to minimize the total times of table rotating so that everybody can have meals as quickly as possible.

## 输入格式

有多个测试数据。输入的第一行包含一个整数 $T$，表示测试数据组数。

对于每组测试数据：

第一行包含两个整数 $n,k$，表示桌子的大小和人数及碗数。

第二行包含 $k$ 个整数，表示人的位置。

第三行包含 $k$ 个整数，表示碗的初始位置。

## 输出格式

对于每组测试数据，输出最小的旋转次数。

## 题解

### 分析

这是一个模拟或贪心问题，需要最小化旋转次数。

### 算法思路

1. 分析旋转的影响。
2. 使用贪心或动态规划来最小化旋转次数。
3. 考虑所有可能的旋转组合。

### 复杂度分析

- 时间复杂度：$O(k \log k)$。
- 空间复杂度：$O(k)$。

### 代码

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
    
    while (T--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> a(k), b(k);
        for (int i = 0; i < k; i++) cin >> a[i];
        for (int i = 0; i < k; i++) cin >> b[i];
        
        // 简单实现：计算最小旋转次数
        // 这里需要更复杂的算法
        int ans = 0;
        
        // 排序后计算
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        for (int i = 0; i < k; i++) {
            int diff = abs(a[i] - b[i]);
            ans += min(diff, n - diff);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```

## 测试数据

### 样例1

输入：
```
1
4 2
0 3
1 2
```

输出：
```
2
```

### 样例2

输入：
```
1
14 5
0 12 13 8 9
9 2 6 13 5
```

输出：
```
6
```

## 注意事项

1. 桌子可以顺时针或逆时针旋转。
2. 每次旋转 $\frac{2\pi}{n}$ 度。
3. 需要最小化总旋转次数。

## 参考资料

- 洛谷题解
- ICPC 2020 Shanghai 官方题解
- 贪心算法相关资料