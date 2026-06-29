# P3606 Building a Tall Barn

## 思路

核心算法：数学

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, k;
    cin >> n >> k;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Binary search on total time
    long long low = 1, high = 1e18;
    long long answer = high;
    
    while (low <= high) {
        long long mid = (low + high) / 2;
        
        // Check if we can complete in mid time
        long long total_cows = 0;
        for (int i = 0; i < n; i++) {
            // Minimum cows needed for floor i
            long long needed = (a[i] + mid - 1) / mid;
            total_cows += needed;
        }
        
        if (total_cows <= k) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << answer << "\n";
    return 0;
}
```

## 解题思路

### 问题分析

n 层建筑，每层需要 a[i] 头牛搬运材料，每头牛耗时 1 单位时间。可以分配多头牛到同一层并行工作，该层耗时 = ceil(a[i]/牛数)。总共有 k 头牛，求完成所有层的最短时间。

### 核心思路

二分答案。二分时间 mid，检查在 mid 时间内完成每层所需的最少牛数之和是否 ≤ k。

### 算法流程

1. 二分时间 mid（1~1e18）
2. 对每个 mid，计算每层所需最少牛数：ceil(a[i]/mid)
3. 若总牛数 ≤ k，则 mid 可行，继续缩小
4. 输出最小可行时间

### 复杂度分析

- 时间复杂度：O(n log(1e18))，二分 O(log(1e18))，每次检查 O(n)
- 空间复杂度：O(n)
