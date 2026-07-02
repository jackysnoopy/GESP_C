# P14591 [LNCPC 2025] Kanon

## 题目描述

给定一个长度为 n 的 01 串 s，将其划分成 k 个非空子段，每个子段看作二进制数（左高位），求所有划分中异或和的最大值及方案数。对 k=1..n 都要求。

## 输入格式

第一行整数 T（测试组数）。
每组一行 01 串 s。

## 输出格式

每行四个整数 A, B, C, D。

## 样例

### 样例 1
输入：
```
5
110
11010
1011010
101111011
11010101101
```
输出：
```
5 2 0 6
19 3 24 9
101 4 109 30
405 7 382 33
1225 6 1144 53
```

## 解题思路

### 问题分析
对于每个 k，枚举所有划分方案，计算异或和，找最大值和方案数。

### 核心思路
- 使用状压 DP 或暴力枚举划分点
- 对于每个 k，计算所有 C(n-1, k-1) 种划分的异或和
- 用 trie 或线性基优化

### 算法流程
1. 枚举所有划分掩码
2. 计算每种划分的异或和
3. 记录最大值和方案数
4. 计算 A, B, C, D

### 复杂度分析
- 暴力: O(2^n * n)
- 优化: O(n^2) 或更优

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        string s;
        cin >> s;
        int n = s.size();
        
        vector<long long> p(n + 1, 0), q(n + 1, 0);
        
        if (n <= 20) {
            int totalMasks = (1 << (n - 1));
            for (int mask = 0; mask < totalMasks; mask++) {
                int bits = __builtin_popcount(mask);
                int k = bits + 1;
                
                long long xorVal = 0;
                long long num = 0;
                for (int i = 0; i < n; i++) {
                    num = num * 2 + (s[i] - '0');
                    if (mask & (1 << i) || i == n - 1) {
                        xorVal ^= num;
                        num = 0;
                    }
                }
                
                if (xorVal > p[k]) {
                    p[k] = xorVal;
                    q[k] = 1;
                } else if (xorVal == p[k]) {
                    q[k]++;
                }
            }
        }
        
        long long A = 0, B = 0, C = 0, D = 0;
        for (int i = 1; i <= n; i++) {
            A ^= p[i];
            B ^= q[i];
            C ^= (p[i] * i);
            D ^= (q[i] * i);
        }
        
        cout << A << " " << B << " " << C << " " << D << "\n";
    }
    
    return 0;
}
```
