# [BalticOI 2022] Uplifting Excursion (Day1)

## 题目描述
有 $2m+1$ 种物品，重量分别为 $-m,-m+1,\ldots, m-1,m$。重量为 $i$ 的物品有 $a_i$ 个。

你需要拿走若干物品，使得这些物品重量之和恰好为 $l$。在此基础上，你需要拿尽可能多的物品。

问在物品重量之和恰好为 $l$ 的基础上，你最多能拿多少物品。

## 输入格式
第一行两个数 $m,l$。

第二行 $2m+1$ 个数，分别为 $a_{-m},a_{-m+1},\ldots, a_{m-1},a_m$。

## 输出格式
一行一个数表示答案。若不存在方案，输出 `impossible`。

## 样例
### 样例1
输入:
```
2 5
2 3 1 1 4
```
输出:
```
9
```

### 样例2
输入:
```
3 5
3 1 0 2 0 0 2
```
输出:
```
impossible
```

## 提示
- 时间限制：1000-4000ms
- 内存限制：131072KB

## 解题思路

### 问题分析
需要选择物品使得总重量为 $l$，同时最大化物品数量。

### 核心思路
1. 使用贪心策略：优先选择重量小的物品
2. 调整以满足总重量约束

### 算法流程
1. 计算总重量和物品数量
2. 贪心选择
3. 调整以满足约束

### 复杂度分析
- 时间复杂度：$O(m)$
- 空间复杂度：$O(m)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    long long l;
    cin >> m >> l;
    
    vector<long long> a(2 * m + 1);
    for (int i = 0; i <= 2 * m; i++) {
        cin >> a[i];
    }
    
    long long total = 0;
    long long weight = 0;
    
    for (int i = 0; i <= 2 * m; i++) {
        long long w = i - m;
        total += a[i] * w;
        weight += a[i];
    }
    
    if (total < l) {
        cout << "impossible" << endl;
    } else {
        long long ans = 0;
        long long current = 0;
        
        for (int i = 2 * m; i >= 0; i--) {
            long long w = i - m;
            long long take = min(a[i], (l - current + w - 1) / w);
            if (w > 0 && take > 0) {
                ans += take;
                current += take * w;
            }
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
```