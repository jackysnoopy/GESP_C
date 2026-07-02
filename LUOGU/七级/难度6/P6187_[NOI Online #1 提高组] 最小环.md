# [NOI Online #1 提高组] 最小环

## 题目描述
长度n的正整数序列视为环。给定k，重排序列使距离为k的数对乘积之和最大。

## 输入格式
第一行n m，第二行a_i，接下来m行每行k_i。

## 输出格式
m行答案。

## 样例
输入：
```
6 4
1 2 3 4 5 6
0
1
2
3
```
输出：
```
91
82
85
88
```

## 解题思路

### 问题分析
- k=0时答案=sum(a_i^2)
- k>0时，将数按大小交替排列到环上

### 核心思路
- 排序后，将最大的n/2个数放在偶数位
- 最小的n/2个数放在奇数位

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
    
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    sort(a.begin(), a.end());
    
    vector<long long> b(n);
    int left = 0, right = n - 1;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) b[i] = a[right--];
        else b[i] = a[left++];
    }
    
    while (m--) {
        int k;
        cin >> k;
        
        if (k == 0) {
            long long ans = 0;
            for (int i = 0; i < n; i++) ans += a[i] * a[i];
            cout << ans << "\n";
        } else {
            long long ans = 0;
            for (int i = 0; i < n; i++) {
                ans += b[i] * b[(i + k) % n];
            }
            cout << ans / 2 << "\n";
        }
    }
    
    return 0;
}
```
