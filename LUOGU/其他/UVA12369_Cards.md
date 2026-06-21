# Cards

## 题目描述

Taha 随身携带了一副标准扑克牌。除 `52` 张常规牌外，还有 `2` 张 Joker 牌。每张常规牌都有点数和花色。点数从低到高依次为：A、2、3、4、5、6、7、8、9、T、J、Q 和 K。

扑克牌的花色可以是梅花、方块、红心或黑桃。这意味着最多有 `13` 张梅花、`13` 张方块、`13` 张红心和 `13` 张黑桃——总计 `52` 张。Joker 牌没有等级或花色。

一天，Sara 向 Taha 发起挑战。她首先将 `54` 张纸牌随机洗牌，然后开始一张接一张地将牌正面朝上摆放在桌上。请问 Sara 期望放置多少张牌，才能确保桌上至少有 `C` 张梅花、`D` 张方块、`H` 张红桃和 `S` 张黑桃？

如果遇到 Joker 牌，Taha 必须将其分配到某种花色，以最小化达到目标所需的平均卡片数量。将 Joker 牌分配到某种花色的决定必须即时做出（即在 Sara 将下一张牌放到桌上之前）。

请注意，两张 Joker 牌的分配并不一定需要相同。

## 输入格式

输入的第一行是一个整数 `T(T<50)`，表示测试用例的数量。每个用例由一行包含 `4` 个整数的顺序组成，分别为 `C`、`D`、`H` 和 `S`。这些整数的取值范围均为 `[0,15]`。

## 输出格式

对于每组测试，首先输出测试编号。然后输出 Sara 要实现目标的期望卡片数量（四舍五入到小数点后 `3` 位）。如果不可能实现目标，输出 `-1.000`。

你可以查看样例以了解更准确的格式。极小的精度误差不会导致答案错误。

## 样例

### 样例输入
```
4
0 0 0 0
15 13 13 13
1 2 3 4
15 15 15 15
```

### 样例输出
```
Case 1: 0.000
Case 2: 54.000
Case 3: 16.393
Case 4: -1.000
```

## 提示

**样例解释**（原题面输出格式下面内容）：

1. 没有必要去放任何一张牌，因此答案是 `0`。
2. 我们必须把 `54` 张牌全放在桌上才能完成目标。
3. 注意答案不一定总是整数。
4. 不可能有 `60` 张牌。

## 解题思路

### 问题分析

扑克牌概率问题，给定四种花色各需的牌数，求期望步数。

### 核心思路

1. 状态压缩 DP：用位表示四种花色是否满足需求。
2. 每次翻牌，根据花色更新状态。
3. 期望 E[S] = 1 + sum(P(next_state) * E[next_state])。

### 算法流程

1. 读入四种花色需求
2. 概率 DP 计算期望
3. 输出答案

### 复杂度分析

时间 O(2^4 * 54)

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int need[4];
double dp[1 << 4][16][16][16][16];

double solve(int mask, int c0, int c1, int c2, int c3) {
    if (mask == 15) return 0;
    double &res = dp[mask][c0][c1][c2][c3];
    if (res >= -0.5) return res;
    int total = 54;
    int rem = total - (13 - c0) - (13 - c1) - (13 - c2) - (13 - c3);
    if (rem == 0) return res = 1e18;
    res = 1;
    int cnt[4] = {c0, c1, c2, c3};
    for (int i = 0; i < 4; ++i) {
        if (cnt[i] > 0) {
            double p = (double)cnt[i] / total;
            int nmask = mask;
            if (cnt[i] <= need[i]) nmask |= (1 << i);
            res += p * solve(nmask, cnt[i] - 1, cnt[(i+1)%4], cnt[(i+2)%4], cnt[(i+3)%4]);
        }
    }
    res += (double)(total - cnt[0] - cnt[1] - cnt[2] - cnt[3]) / total * 1;
    return res;
}

int main() {
    int cs = 0;
    while (scanf("%d%d%d%d", &need[0], &need[1], &need[2], &need[3]) == 4) {
        if (need[0] + need[1] + need[2] + need[3] == 0) break;
        memset(dp, -1, sizeof(dp));
        double ans = solve(0, 13, 13, 13, 13);
        printf("Case %d: ", ++cs);
        if (ans > 1e17) printf("-1.000\n");
        else printf("%.3f\n", ans);
    }
    return 0;
}
```
