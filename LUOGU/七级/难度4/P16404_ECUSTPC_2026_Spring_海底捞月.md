# [ECUSTPC 2026 Spring] 海底捞月

## 题目描述

:::epigraph
___, ___ 面色一沉：河底捞鱼是什么意思？
:::

TSUCE 的期末考试结束了！阅卷老师大 K 看了看小 T 惨不忍睹的试卷。  

因此他决定使用以下的招数，拯救考了 $x$ 分的小 T：

- 【连根拔起】，这个招数至多可以使用 $a_1$ 次，将小 T 当前的分数 $x$ 开根号乘 $10$ 下取整，也即 $x \leftarrow \lfloor 10\sqrt{x} \rfloor$.
- 【三七分成】，这个招数至多可以使用 $a_2$ 次，将小 T 当前的分数 $x$ 乘上 $0.7$ 再加上 $30$ 再下取整，也即 $x \leftarrow \lfloor 0.7x + 30 \rfloor$.
- 【种五得六】，这个招数至多可以使用 $a_3$ 次，将小 T 当前的分数 $x$ 乘上 $1.2$ 再下取整，也即 $x \leftarrow \lfloor 1.2x \rfloor$.
- 【五福临门】，这个招数至多可以使用 $a_4$ 次，将小 T 当前的分数 $x$ 加 $5$，也即 $x \leftarrow x + 5$.

四种招数可以按任意顺序使用，请帮大 K 求出一个合理的使用招数的方式，来让小 T 获得最高的分数。

## 输入格式

第一行输入一个整数 $T\ (1 \le T \le 3 \times 10^5)$，表示测试数据的数量。  

每组测试数据输入一行 $5$ 个整数 $x, a_1, a_2, a_3, a_4\ (1 \le x \le 100, 0 \le a_1, a_2, a_3, a_4 \le 400)$，表示小 T 的初始分数，以及四种招数的可用次数上限。

## 输出格式

对于每组测试数据，输出一行一个整数表示小 T 可以获得的最高分数。

## 样例

### 样例输入 1
```
7
1 1 1 1 1
50 2 1 1 2
99 0 1 2 1
10 2 0 0 3
100 400 400 400 400
75 1 7 3 0
1 3 7 4 3
```

### 样例输出 1
```
70
118
148
71
98703086085238798121046930830507710
168
232
```

## 提示

### 样例 1 解释

对于第 $1$ 组测试数据，小 T 一开始豪取 $1$ 分，大 K 每种招数都至多能使用一次，大 K 可以采用如下的策略：

- 首先用【三七分成】，小 T 变为 $\lfloor 0.7x + 30 \rfloor = \lfloor 0.7 \times 1 + 30 \rfloor = 30$ 分。
- 随后用【连根拔起】，小 T 变为 $\lfloor 10\sqrt{x} \rfloor = \lfloor 10\sqrt{30} \rfloor = 54$ 分。
- 随后用【五福临门】，小 T 变为 $54 + 5 = 59$ 分。
- 随后用【种五得六】，小 T 变为 $\lfloor 1.2x \rfloor = \lfloor 1.2 \times 59 \rfloor = 70$ 分。

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
