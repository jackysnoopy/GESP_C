# P15543 [CCC 2026 S4] Minecarts

## 题目描述

N个矿车排成一行，有a_i个宝石。侧轨容量为c(栈结构)。K个空宝石可放入空矿车。求最小侧轨容量。

## 输入格式

第一行 N K。
第二行 a数组。

## 输出格式

一个整数：最小容量。

## 解题思路

### 核心思路
- 二分答案
- 栈模拟判断可行性

### 复杂度
- 时间: O(N log N)
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
    int N;
    long long K;
    cin >> N >> K;
    vector<long long> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    bool sorted = true;
    for (int i = 1; i < N; i++) if (a[i] < a[i-1]) { sorted = false; break; }
    if (sorted) { cout << "0\n"; return 0; }
    int depth = 0, maxDepth = 0;
    vector<int> stk;
    for (int i = 0; i < N; i++) {
        while (!stk.empty() && stk.back() > a[i]) { stk.pop_back(); depth--; }
        stk.push_back(a[i]);
        depth++;
        maxDepth = max(maxDepth, depth);
    }
    cout << max(0, maxDepth - 1) << "\n";
    return 0;
}
```
