# P12026 [USACO25OPEN] Compatible Pairs S

## 题目描述

Farmer John 有 $N$ 种不同 ID 的牛，每种 ID $d_i$ 有 $n_i$ 头。两头牛可以通信当且仅当它们的 ID 之和等于 $A$ 或 $B$。每头牛只能参与一个配对。求最大配对数。

## 输入格式

第一行 $N, A, B$。接下来 $N$ 行每行 $n_i, d_i$。

## 输出格式

一个整数，最大配对数。

## 样例

**输入样例 1**
```
4 4 5
17 2
100 0
10 1
200 4
```
**输出样例 1**
```
118
```

## 解题思路

### 问题分析

每个配对要求两头牛的 ID 之和等于 $A$ 或 $B$。这是一个最大匹配问题，但由于配对条件简单（只看和），可以用贪心解决。

### 核心思路

1. **自配对**：若 $2d = A$ 或 $2d = B$，同 ID 的牛可以自配对，配对数为 $\lfloor n_d / 2 \rfloor$。
2. **交叉配对**：对于目标和 $T \in \{A, B\}$，枚举 $(d, T-d)$ 对，配对数为 $\min(n_d, n_{T-d})$。
3. **顺序问题**：当一个 ID 同时参与 $A$ 和 $B$ 的配对时，顺序影响结果。枚举两种顺序取最优。

### 复杂度分析

- 时间复杂度：$O(N \log N)$
- 空间复杂度：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long A, B;
    cin >> N >> A >> B;
    
    map<long long, long long> cnt;
    for (int i = 0; i < N; i++) {
        long long d, n;
        cin >> n >> d;
        cnt[d] = n;
    }
    
    long long ans = 0;
    // 自配对
    for (map<long long, long long>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if (2 * it->first == A) { ans += it->second / 2; it->second %= 2; }
        if (2 * it->first == B && A != B) { ans += it->second / 2; it->second %= 2; }
    }
    
    // 枚举两种顺序取最优
    long long best = 0;
    for (int order = 0; order < 2; order++) {
        map<long long, long long> tmp = cnt;
        long long cur = ans;
        vector<long long> tg = (order == 0) ? vector<long long>{A, B} : vector<long long>{B, A};
        if (A == B) tg.resize(1);
        for (int ti = 0; ti < (int)tg.size(); ti++) {
            long long T = tg[ti];
            for (map<long long, long long>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
                if (it->first * 2 > T) break;
                long long need = T - it->first;
                if (need == it->first) continue;
                map<long long, long long>::iterator jt = tmp.find(need);
                if (jt != tmp.end() && jt->second > 0 && it->second > 0) {
                    long long pairs = min(it->second, jt->second);
                    cur += pairs;
                    it->second -= pairs;
                    jt->second -= pairs;
                }
            }
        }
        best = max(best, cur);
    }
    cout << best << endl;
    return 0;
}
```
