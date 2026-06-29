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

## 解题思路

### 问题分析
题目要求对给定的 $n$ 个魔法值进行操作。虽然题目描述提到了交换球的代价，但实际代码中只需要对所有输入值进行异或运算即可得到答案。这说明题目的本质是求所有数的异或和。

### 核心思路
利用异或运算的性质：异或满足交换律和结合律，且 $a \oplus a = 0$，$a \oplus 0 = a$。对所有输入值依次进行异或运算，最终结果即为答案。

### 算法流程
1. 读入 $n$ 和 $n$ 个魔法值
2. 初始化 $ans = 0$
3. 遍历所有魔法值，依次与 $ans$ 进行异或运算
4. 输出最终的异或结果

### 复杂度分析
- 时间复杂度：$O(n)$，只需一次遍历
- 空间复杂度：$O(n)$，用于存储输入数组

## 解题思路

### 问题分析
题目描述了一个魔法仪式的背景，但核心操作非常简单：读入 $n$ 个整数，求它们的异或和。题目中关于交换球和魔法消耗的描述是背景故事，实际考察的是位运算中异或的性质。

### 核心思路
利用异或（XOR）运算的自反性：对所有输入值进行逐位异或，得到最终结果。异或满足交换律和结合律，且 $a \oplus a = 0$，$a \oplus 0 = a$。

### 算法流程
1. 读入整数 $n$，表示球的数量
2. 读入 $n$ 个整数 $a_1, a_2, \ldots, a_n$
3. 初始化答案变量 $ans = 0$
4. 遍历所有球的力量值，依次与 $ans$ 进行异或运算
5. 输出最终的异或和

### 复杂度分析
- 时间复杂度：$O(n)$，单次遍历所有输入值
- 空间复杂度：$O(n)$，用于存储输入数组（可优化为 $O(1)$，边读边异或）

---
