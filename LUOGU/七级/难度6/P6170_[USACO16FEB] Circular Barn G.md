# [USACO16FEB] Circular Barn G

## 题目描述
n个房间排成环形，第i个房间有c_i头奶牛(sum c_i=n)。奶牛顺时针穿过d扇门消耗d^2能量。求最小总能量。

## 输入格式
第一行n，接下来n行每行c_i。

## 输出格式
最小能量。

## 样例
输入：
```
10
1
0
0
2
0
0
1
2
2
2
```
输出：
```
33
```

## 解题思路

### 问题分析
- 环形问题，断环为链
- 前缀和+均值不等式

### 核心思路
- 每段奶牛的最优位置在中位数处
- 枚举断点，用前缀和优化

### 复杂度分析
- 时间复杂度：O(n^2)
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
    
    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c[i]; j++) {
            pos.push_back(i);
        }
    }
    
    int m = pos.size();
    long long ans = 1e18;
    
    for (int start = 0; start < n; start++) {
        long long total = 0;
        int idx = 0;
        for (int i = 0; i < m; i++) {
            int dist = (pos[i] - start + n) % n;
            total += (long long)dist * dist;
        }
        ans = min(ans, total);
    }
    
    cout << ans << "\n";
    return 0;
}
```
