# P15263 [USACO26JAN2] Circle of Cows P

## 题目描述

N头牛在圆周上不同位置，选k对牛使同一对中两牛的最小圆周距离最大。对k=1..N/2都要求。

## 输入格式

第一行 N C。
第二行 l数组。

## 输出格式

一行：k=1..N/2的答案。

## 解题思路

### 核心思路
- 二分答案
- 贪心配对

### 复杂度
- 时间: O(N^2 log C)
- 空间: O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, C;
    cin >> n >> C;
    vector<int> pos(n);
    for (int i = 0; i < n; i++) cin >> pos[i];
    int maxK = n / 2;
    for (int k = 1; k <= maxK; k++) {
        int lo = 0, hi = C / 2, ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            bool found = false;
            for (int start = 0; start < n && !found; start++) {
                vector<int> used(n, 0);
                int paired = 0;
                for (int i = 0; i < n && paired < k; i++) {
                    int idx = (start + i) % n;
                    if (used[idx]) continue;
                    for (int j = i + 1; j < n && paired < k; j++) {
                        int jdx = (start + j) % n;
                        if (used[jdx]) continue;
                        int d = abs(pos[idx] - pos[jdx]);
                        d = min(d, C - d);
                        if (d >= mid) { used[idx] = 1; used[jdx] = 1; paired++; break; }
                    }
                }
                if (paired >= k) found = true;
            }
            if (found) { ans = mid; lo = mid + 1; } else hi = mid - 1;
        }
        cout << ans << (k < maxK ? " " : "\n");
    }
    return 0;
}
```
