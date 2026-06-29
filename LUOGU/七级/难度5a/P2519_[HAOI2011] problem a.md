# P2519 [HAOI2011] problem a

## 思路

核心算法：贪心+计数

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
    
    vector<pair<int, int>> claims(n);
    for (int i = 0; i < n; i++) {
        cin >> claims[i].first >> claims[i].second;
    }
    
    // Count how many people claim to be at each rank
    vector<int> count(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        int a = claims[i].first;
        int b = claims[i].second;
        
        // If a + b >= n, the claim is invalid
        if (a + b >= n) continue;
        
        // The person claims to be at rank a + 1 (0-indexed: a)
        int rank = a + 1;
        if (rank >= 1 && rank <= n) {
            count[rank]++;
        }
    }
    
    // For each rank, at most one person can be telling the truth
    int truth = 0;
    for (int i = 1; i <= n; i++) {
        truth += min(count[i], 1);
    }
    
    cout << n - truth << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
n个人参与排名，每人知道自己的名次之前有多少人比自己好（a人）和之后有多少人比自己差（b人）。由于排名是1到n的整数，每个人的回答可以转换为：该人声称自己排在第(a+1)位。问最少有多少人撒谎。

### 核心思路
每个人的回答可以确定一个可能的排名。对于每个排名位置，至多只能有一个人真实地排在那里。因此，对于每个排名位置i，若有多人声称排在第i位，那么其中至多1人说真话，其余人都撒谎。通过统计每个排名被声称的次数，可以计算出最多有多少人说真话，从而得出最少撒谎人数。

### 算法流程
1. 读入n个人的回答(a, b)
2. 对每个人，若a+b < n，则该人声称自己排在第(a+1)位，在对应位置计数+1
3. 对每个排名位置i（1到n），若count[i] >= 1，则至多1人说真话
4. 真话总数 = sum(min(count[i], 1))
5. 最少撒谎人数 = n - 真话总数
6. 输出最少撒谎人数

### 复杂度分析
- 时间复杂度：O(n)，单次遍历统计
- 空间复杂度：O(n)，计数数组
