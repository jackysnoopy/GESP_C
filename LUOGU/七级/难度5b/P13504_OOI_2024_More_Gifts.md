# [OOI 2024] More Gifts

## 题目描述

k 个相同的礼物栈（每栈 n 个礼物），依次从栈 1 到栈 k 分发。每个参与者最多接收 t 种不同类型礼物。求最少参与者数。

## 输入格式

第一行 n, k, t，第二行 n 个礼物类型。

## 输出格式

一个整数。

## 样例

```
2 4 1
1 2
```

输出：8

## 解题思路

### 问题分析
礼物按固定顺序分发（栈1从上到下→栈2从上到下→...）。每个参与者连续接收礼物，但不同类型不能超过 t 种。

### 核心思路
贪心扫描：每个参与者尽可能多地接收礼物，直到会引入第 t+1 种类型时停止。

### 算法流程
1. 按顺序扫描 n×k 个礼物
2. 每个参与者维护已接收类型集合
3. 当即将引入新类型且已达上限时，换下一个参与者

### 复杂度分析
- 时间：O(n×k)
- 空间：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; long long t;
    cin >> n >> k >> t;
    vector<int> a(n);
    for (int i=0;i<n;i++) cin>>a[i];
    long long total = (long long)n*k;
    vector<int> types = a;
    sort(types.begin(), types.end());
    types.erase(unique(types.begin(), types.end()), types.end());
    if ((int)types.size() <= t) { cout<<1<<"\n"; return 0; }
    long long ans = 0, pos = 0;
    while (pos < total) {
        ans++;
        vector<bool> has(1000001, false);
        int dc = 0;
        while (pos < total) {
            int type = a[pos%n];
            if (!has[type]) {
                if (dc >= (int)t) break;
                has[type] = true; dc++;
            }
            pos++;
        }
    }
    cout << ans << "\n";
    return 0;
}
```
