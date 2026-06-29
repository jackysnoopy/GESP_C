# P3042 [USACO12JAN] Cow Run G

## 思路

核心算法：博弈论 + 记忆化搜索

## 代码

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int N;
long long M, K;
vector<vector<long long>> cards;
map<pair<long long, int>, bool> memo;

bool canGuarantee(long long d, int i) {
    if (i == N) {
        return d <= K || (M - d <= K && d > 0);
    }
    auto key = make_pair(d, i);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    long long a1 = (1 + cards[i][0]) % M, b1 = cards[i][1] % M;
    long long a2 = (1 + cards[i][2]) % M, b2 = cards[i][3] % M;
    long long a3 = (1 + cards[i][4]) % M, b3 = cards[i][5] % M;
    long long a4 = (1 + cards[i][6]) % M, b4 = cards[i][7] % M;
    long long dt1 = (d * a1 + b1) % M;
    long long dt2 = (d * a2 + b2) % M;
    if (canGuarantee(dt1, i + 1) && canGuarantee(dt2, i + 1)) {
        return memo[key] = true;
    }
    long long db1 = (d * a3 + b3) % M;
    long long db2 = (d * a4 + b4) % M;
    return memo[key] = (canGuarantee(db1, i + 1) && canGuarantee(db2, i + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> K;
    string bessie;
    cin >> bessie;
    cards.resize(N, vector<long long>(8));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 8; j++)
            cin >> cards[i][j];
    string answer;
    long long d = 0;
    for (int i = 0; i < N; i++) {
        long long a1 = (1 + cards[i][0]) % M, b1 = cards[i][1] % M;
        long long a2 = (1 + cards[i][2]) % M, b2 = cards[i][3] % M;
        long long a3 = (1 + cards[i][4]) % M, b3 = cards[i][5] % M;
        long long a4 = (1 + cards[i][6]) % M, b4 = cards[i][7] % M;
        long long dt1 = (d * a1 + b1) % M;
        long long dt2 = (d * a2 + b2) % M;
        if (canGuarantee(dt1, i + 1) && canGuarantee(dt2, i + 1)) {
            answer += 'T';
            d = (bessie[i] == 'T') ? dt1 : dt2;
        } else {
            answer += 'B';
            long long db1 = (d * a3 + b3) % M;
            long long db2 = (d * a4 + b4) % M;
            d = (bessie[i] == 'T') ? db1 : db2;
        }
    }
    cout << answer << "\n";
    return 0;
}
```

## 解题思路

### 问题分析

N轮游戏，每轮8张牌。FJ选上4或下4给Bessie，Bessie从中选上2或下2。FJ喊X_top，Bessie喊X_bottom，牛跑 R*X_top + X_bottom 距离（R为累计距离）。最终位置必须在起点K范围内才能回家。

### 核心思路

博弈论记忆化搜索。从当前位置d开始，FJ需要选择一个策略使得无论Bessie怎么选，最终都能回家。

### 算法流程

1. 定义 canGuarantee(d, i)：从位置d、第i轮开始，FJ能否保证回家
2. 终止条件：所有轮结束，检查位置是否在K范围内
3. 递归：尝试FJ选T或B，检查两个Bessie响应是否都能回家
4. 贪心确定答案：每轮优先选T（字典序最小）

### 复杂度分析

- 时间复杂度：O(N × 2^N)，记忆化搜索
- 空间复杂度：O(N × 2^N)，记忆化表
