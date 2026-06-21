# [GCJ 2013 #2] Many Prizes

## 题目描述

We're going to run a tournament with $2^N$ teams, and give out $P$ identical prizes to the teams with ranks $0\dots P-1$.

The teams are numbered $0$ through $2^N-1$. When team $i$ and team $j$ play against each other in a game, team $i$ will win iff $i  [W, W, L] > [W, L, W] > [L, L, L]$.

Here is an example of a tournament with $N=3$, and the tournament list $[2, 4, 5, 3, 6, 7, 1, 0]$, where the columns represent different rounds, and the teams are grouped by their records. The winner of each game in the example has been marked with a $*$.

![](https://cdn.luogu.com.cn/upload/image_hosting/mxtuvhs2.png)

If we give out $4$ prizes ($N=3, P=4$), the prizes will go to teams $0$, $2$, $3$ and $6$.

The largest-numbered team that was guaranteed to win a prize with $N=3, P=4$, independent of the order of the tournament list, was team $0$: this tournament list demonstrated that it's possible for team $1$ not to win a prize, and it turns out that team $0$ will always win one, regardless of the order of the tournament list.

The largest-numbered team that could win a prize with $N=3, P=4$, depending on how the tournament list was ordered, was team $6$: this tournament list demonstrated that it's possible for team $6$ to win a prize, and it turns out that team $7$ will never win one, regardless of the order of the tournament list.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case consists of two space-separated integers: $N$, which indicates the tournament has $2^N$ teams, and $P$, the number of prizes.

## 输出格式

For each test case, output one line containing "Case #x: y z", where $x$ is the case number (starting from 1), $y$ is the largest-numbered team that is guaranteed to win a prize, independent of how the tournament list is ordered; and $z$ is the largest-numbered team that could win a prize, depending on how the tournament list is ordered.

## 样例

### 样例输入 1
```
3
3 4
3 5
3 3
```

### 样例输出 1
```
Case #1: 0 6
Case #2: 2 6
Case #3: 0 4
```

## 提示

**Limits**

* $1 \leq T \leq 100$.
* $1 \leq P \leq 2^N$.

**Small dataset (7 Pts, Test set 1 - Visible)**

* $1 \leq N \leq 10$.

**Large dataset (13 Pts, Test set 2 - Hidden)**

* $1 \leq N \leq 50$.

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

    for (int t = 1; t <= T; t++) {
        int N, P;
        cin >> N >> P;

        long long total = 1LL << N;
        long long guaranteed = 0;
        long long possible = 0;

        for (long long team = 0; team < total; team++) {
            bool can_win = true;
            for (long long other = team + 1; other < total; other++) {
                if (__builtin_popcountll(team & other) > 0) {
                    can_win = false;
                    break;
                }
            }
            if (can_win) guaranteed = team;
        }

        for (long long team = total - 1; team >= 0; team--) {
            bool can_win = false;
            for (long long other = 0; other < total; other++) {
                if (other != team && __builtin_popcountll(team & other) == 0) {
                    can_win = true;
                    break;
                }
            }
            if (can_win) {
                possible = team;
                break;
            }
        }

        cout << "Case #" << t << ": " << guaranteed << " " << possible << "\n";
    }

    return 0;
}
```
