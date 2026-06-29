# P1561 [USACO12JAN] Mountain Climbing S

## 思路

核心算法：贪心调度

## 代码

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
    
    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
    }
    
    sort(cows.begin(), cows.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    
    long long up_time = 0;
    long long down_time = 0;
    
    for (int i = 0; i < n; i++) {
        up_time += cows[i].first;
        down_time = max(down_time, up_time) + cows[i].second;
    }
    
    cout << down_time << "\n";
    return 0;
}
```

## 解题思路

### 问题分析

n 头牛依次上山再下山，第 i 头牛上山耗时 up[i]，下山耗时 down[i]。牛必须按顺序上山，但下山可以在任何时间。求所有牛完成上下山的最短时间。

### 核心思路

贪心调度。按 down[i] 降序排序，先下山时间长的牛先上山，这样下山时间长的牛有更多时间下山，减少等待。

### 算法流程

1. 按 down[i] 降序排序
2. 顺序处理每头牛：
   - up_time += up[i]（上山累计时间）
   - down_time = max(down_time, up_time) + down[i]
3. 输出 down_time

### 复杂度分析

- 时间复杂度：O(n log n)，排序主导
- 空间复杂度：O(n)
