# [ECUSTPC 2026 Spring] 烈焰风暴 2

## 题目描述

:::epigraph
你需要我的帮助？
:::

奶龙正在游戏内杀怪，这是一个回合制游戏，他遭遇了 $n$ 只怪物，它们的生命值分别为 $h_1, h_2, \dots, h_n$.

每个回合，奶龙可以选择释放下面其中一个技能一次：

- 火球术，选定一只怪物，对其造成 $x$ 点伤害，并消耗奶龙 $a$ 点法力值。
- 烈焰风暴，对所有怪物造成 $y$ 点伤害，并消耗奶龙 $b$ 点法力值。

当怪物受到伤害时会扣减等量的生命值，若其生命值小于等于 $0$, 怪物将会被击杀，当所有 $n$ 只怪物被击杀时则奶龙赢得战斗胜利。

请帮助奶龙规划技能使用，使其消耗的法力值最小并赢得战斗，并求出需要消耗的最小法力值。

## 输入格式

本题每个测试点只有一组测试数据。

第一行输入 $5$ 个整数 $n, x, y, a, b\ (1 \le n, x, y, a, b \le 2 \times 10^6)$，分别表示怪物的数量，火球术和烈焰风暴的伤害，以及这两个技能对应的法力值消耗。

随后一行输入 $n$ 个整数 $h_1, h_2, \dots, h_n\ (1 \le h_i \le 10^7)$，表示怪物的血量。

## 输出格式

输出一行一个整数，表示奶龙赢得战斗所需消耗的最小法力值。

## 样例

### 样例输入 1
```
4 10 8 5 7
9 17 23 40
```

### 样例输出 1
```
31
```

### 样例输入 2
```
5 3 1 2 5
1 2 3 4 10
```

### 样例输出 2
```
17
```

## 提示

### 样例 1 解释

此时奶龙一种可行的技能使用方案是使用 $3$ 次烈焰风暴，随后再对最后一只怪物使用 $2$ 次火球术。

这样其他怪物受到 $8 \times 3 = 24$ 点伤害，最后一只怪物受到 $24 + 10 \times 2 = 44$ 点伤害，都被击杀。

此时法力值消耗为 $3 \times 7 + 2 \times 5 = 31$ 点，可以证明这是最优的。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long x;
        int a1, a2, a3, a4;
        cin >> x >> a1 >> a2 >> a3 >> a4;

        long long best = x;

        for (int mask = 0; mask < (1 << 4); mask++) {
            int cnt[4] = {0};
            for (int i = 0; i < 4; i++) {
                if (mask & (1 << i)) cnt[i]++;
            }

            long long val = x;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < cnt[i]; j++) {
                    if (i == 0) val = (long long)(10 * sqrt(val));
                    else if (i == 1) val = (long long)(0.7 * val + 30);
                    else if (i == 2) val = (long long)(1.2 * val);
                    else val = val + 5;
                }
            }

            best = max(best, val);
        }

        cout << best << "\n";
    }

    return 0;
}
```
