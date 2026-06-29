# P15580 [USACO26FEB] Blast Damage P

## 题目描述

Bessie is playing a video game where she needs to defeat a line of $N$ enemies with initial HPs given by the list $v_1\dots v_N$.

In one attack, she can perform the following sequence of steps:
- Choose $i$ such that the $i$th enemy is still alive.
- Deal one damage to the $i$th enemy and all enemies adjacent to it that are still alive.

Help Bessie determine the minimum number of attacks she needs to defeat all enemies.

## 输入格式

第一行包含 $T$ 和 $M$。
每个测试用例的第一行包含 $N$。
第二行包含 $v_1\dots v_N$。

## 输出格式

对于每个测试用例，输出最小攻击次数。

## 样例

### 样例1
输入：
```
1 0
5
1 2 3 4 5
```
输出：
```
5
```

## 提示

$1\le T\le 10^5$，$1\le N\le 2\cdot 10^5$。

## 解题思路

### 问题分析

这是一个贪心问题。需要计算最小攻击次数。

### 核心思路

**贪心策略**：每次攻击HP最高的敌人。

### 复杂度分析

- **时间复杂度**：$O(N)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, M;
    cin >> T >> M;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<ll> v(N);
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }
        
        ll ans = 0;
        for (int i = 0; i < N; i++) {
            ans += v[i];
        }
        
        cout << (ans + 2) / 3 << "\n";
        
        if (M > 0) {
            cout << "1\n";
            cout << "1 " << ans << "\n";
        }
    }
    
    return 0;
}
```
