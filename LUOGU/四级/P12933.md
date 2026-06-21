# P12933 [NOISG 2020 Prelim] Solar Storm

## 题目描述

Squeaky 老鼠是宇宙飞船的船长，正在执行探索太阳系边界的任务。飞船呈长条状，沿着飞船的长度方向有一条笔直的通道，$N$ 个舱室连接在通道的不同位置。舱室从左到右编号为 $1$ 到 $N$，相邻舱室之间的距离不一定相等。

每个舱室 $i$（$1 \leq i \leq N$）中都有重要的设备，用于支持飞船的运行，设备的重要性用正整数 $v_i$ 表示。相邻舱室之间有电缆连接，设备可以通过其他舱室远程控制。

一场太阳风暴即将袭击飞船！船员随船携带了 $S$ 个防护盾。每个防护盾可以放置在任意舱室，保护半径为 $K$ 米，半径范围内的所有舱室设备都能被保护。

需要注意：所有被保护的舱室之间必须可以相互控制设备，即被保护的舱室之间不能存在未被保护的舱室。

请你确定防护盾的最优放置方案，最大化被保护舱室的重要性总和，并保证控制连通性。

## 输入格式

第一行三个整数 $N,\ S,\ K$。

第二行 $N - 1$ 个整数 $d_i$，第 $i$ 个舱室与第 $i+1$ 个舱室之间的距离。

第三行 $N$ 个整数 $v_i$，第 $i$ 个舱室的重要性。

## 输出格式

第一行一个整数 $T$，表示实际使用的防护盾数量。

第二行 $T$ 个整数，表示放置防护盾的舱室编号。

## 样例

**输入样例 1**
```
6 2 7
10 4 7 18 11
5 8 2 4 8 12
```
**输出样例 1**
```
2
3 5
```

**输入样例 2**
```
6 2 38
10 4 7 18 11
5 8 2 4 8 12
```
**输出样例 2**
```
1
1
```

**输入样例 3**
```
6 1 12
10 4 7 18 11
5 8 2 4 8 12
```
**输出样例 3**
```
1
4
```

**输入样例 4**
```
12 1 2
1 1 1 1 1 1 1 1 1 1 1
1 2 3 4 5 6 6 5 4 3 2 1
```
**输出样例 4**
```
1
4
```

**输入样例 5**
```
10 3 1
2 2 2 2 2 2 2 2 2
3 7 5 6 8 4 3 2 2 9
```
**输出样例 5**
```
3
3 4 5
```

## 提示

**数据范围**

- $1 \leq S \leq N \leq 10^6$
- $1 \leq K \leq 10^{12}$
- $1 \leq d_i \leq 10^6$
- $1 \leq v_i \leq 10^6$

## 解题思路

### 问题分析

由于所有被保护的舱室必须形成一个连续区间（连通性要求），问题转化为：选择一个连续区间 $[l, r]$，用不超过 $S$ 个防护盾覆盖它，使得区间内重要性总和最大。

### 核心思路：贪心覆盖 + 倍增

**贪心覆盖**：对于起始位置 $i$，贪心地放置防护盾——每个防护盾放在能覆盖当前位置的最右舱室，使覆盖范围最大化。

定义 $g[i]$：从舱室 $i$ 开始，放一个防护盾能覆盖到的最远舱室。

- 能覆盖 $pos[i]$ 的最右舱室 $x$ 满足 $pos[x] \leq pos[i] + K$
- 该防护盾覆盖到 $pos[x] + K$
- $g[i]$ = 最大的 $j$ 使得 $pos[j] \leq pos[x] + K$

**倍增加速**：定义 $next(i) = g[i] + 1$（放一个防护盾后下一个需要覆盖的位置）。

用倍增预处理 $jump[j][i]$ = 从 $i$ 开始放 $2^j$ 个防护盾后的下一个位置。

对于每个起始位置 $i$，用二进制分解 $S$ 计算放 $S$ 个防护盾能覆盖到的最远舱室。

### 算法流程

1. 计算前缀位置和前缀重要性和
2. 预处理 $g[i]$（二分查找）
3. 倍增预处理 $jump$
4. 枚举起始位置，找最大重要性区间
5. 在最优区间内贪心放置防护盾并输出

### 复杂度分析

- **时间复杂度**：$O(N \log N)$（二分查找 + 倍增）
- **空间复杂度**：$O(N \log S)$

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

    int n, s;
    ll k;
    cin >> n >> s >> k;

    vector<ll> d(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> d[i];

    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    // 前缀和：位置和重要性（1-indexed）
    vector<ll> pos(n + 1, 0);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pos[i + 1] = pos[i] + (i < n - 1 ? d[i] : 0);
        pref[i + 1] = pref[i] + v[i];
    }

    // g[i]：从i开始放一个防护盾能覆盖到的最远舱室
    vector<int> g(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        ll limit = pos[i] + k;
        int x = (int)(upper_bound(pos.begin() + 1, pos.begin() + n + 1, limit) - pos.begin() - 1);
        ll cover = pos[x] + k;
        g[i] = (int)(upper_bound(pos.begin() + 1, pos.begin() + n + 1, cover) - pos.begin() - 1);
    }
    g[n + 1] = n;

    // 倍增预处理
    int LOG = 21;
    vector<vector<int>> jump(LOG, vector<int>(n + 2));
    for (int i = 1; i <= n + 1; i++) {
        jump[0][i] = min(g[i] + 1, n + 1);
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n + 1; i++) {
            jump[j][i] = jump[j - 1][jump[j - 1][i]];
        }
    }

    // 枚举起始位置，找最大重要性区间
    ll ans_sum = 0;
    int ans_l = 1, ans_r = 1;

    for (int i = 1; i <= n; i++) {
        int cur = i;
        int rem = s;
        for (int j = LOG - 1; j >= 0; j--) {
            if (rem >= (1 << j)) {
                cur = jump[j][cur];
                rem -= (1 << j);
            }
        }
        int r = cur - 1;
        if (r < i) r = i - 1;
        ll sum = pref[r] - pref[i - 1];
        if (sum > ans_sum) {
            ans_sum = sum;
            ans_l = i;
            ans_r = r;
        }
    }

    // 贪心放置防护盾
    vector<int> shields;
    int cur_pos = ans_l;
    while (cur_pos <= ans_r && (int)shields.size() < s) {
        shields.push_back(cur_pos);
        cur_pos = g[cur_pos] + 1;
    }

    cout << shields.size() << "\n";
    for (int i = 0; i < (int)shields.size(); i++) {
        if (i > 0) cout << " ";
        cout << shields[i];
    }
    cout << "\n";

    return 0;
}
```
