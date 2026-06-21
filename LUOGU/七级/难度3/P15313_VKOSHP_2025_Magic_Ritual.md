# [VKOSHP 2025] Magic Ritual

## 题目描述

At the Academy of Archmages, there is a special tradition: every graduate must master the ritual of sorting magical spheres perfectly.

On a long altar, there are $n$ spheres placed from left to right, each numbered. Each sphere has a given strength, and to successfully complete the ritual, they must be arranged in non-decreasing order of strength. To achieve this, spheres can be swapped, and in one action, any two spheres can be exchanged.

However, the magical flow between two positions $i$ and $j$ is unstable, and swapping the spheres at these positions requires spending $(i - j - 2)^2$ units of mana.

The ritual is considered complete when the spheres are arranged in the correct order. You need to conduct the ritual in such a way that the total mana expenditure is minimized.

You will need to answer several independent queries about conducting the rituals.

## 输入格式

The first line contains an integer $t$ ($1 \le t \le 2 \cdot 10^5$) --- the number of rituals.

The descriptions of the rituals follow.

In the first line of each ritual, there is a number $n$ ($1 \le n \le 2 \cdot 10^5$) --- the number of spheres.

In the second line, $n$ integers $a_1, a_2, \dots, a_n$ are given ($0 \le a_i \le 10^9$) --- the strength of each sphere.

It is guaranteed that the sum of $n$ across all rituals does not exceed $2 \cdot 10^5$.

## 输出格式

For each ritual, output a single integer --- the minimum mana expenditure to complete the ritual.

## 样例

### 样例输入 1
```
3
3
3 2 1
3
2 1 2
4
4 3 2 1
```

### 样例输出 1
```
0
1
2
```

## 提示

难度：普及/提高−

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

    vector<int> spells(n);
    for (int i = 0; i < n; i++) cin >> spells[i];

    int ans = 0;
    for (int s : spells) ans ^= s;

    cout << ans << "\n";
    return 0;
}
```
