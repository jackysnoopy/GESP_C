# [GCJ 2022 #1C] Letter Blocks

## 题目描述

It is a rainy day, so you are indoors building towers of letter blocks. A letter block is a wooden cube that has a letter printed on one of its sides. The font used for the letters makes the blocks have a clear orientation: that is, there is only one side that can be pointed down (toward the floor) and one side that can be pointed up (toward the ceiling).

You have built multiple separate towers so far. Now you want to combine all of them into a single megatower by choosing one of your towers as the base, then picking up another tower (without changing the order of its blocks) and stacking the whole thing on top of that, and so on, until all towers have been used.

As an additional constraint for the megatower, for any two blocks that have the same letter, all blocks between them must also have that letter. That is, each letter of the alphabet that appears in the megatower needs to appear in one contiguous group (of one or more blocks).

For example, consider the following three possible megatowers. (These are separate examples, not built from the same original towers. Also note that the different block sizes are just for fun and are not part of the problem.)

![](https://cdn.luogu.com.cn/upload/image_hosting/s3qed2k7.png)

The leftmost two megatowers are valid, since each letter appears in a contiguous group. However, the rightmost megatower is not valid, because there is a B in between two Cs.

Given the towers that you have built so far, can you stack them all up into a valid megatower?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case is described by two lines. The first line consists of a single integer $\mathbf{N}$, the number of towers that are currently built. The second line consists of $\mathbf{N}$ strings $\mathbf{S}_{1}, \mathbf{S}_{2}, \ldots, \mathbf{S}_{\mathbf{N}}$ representing the towers. Each of these strings consists of only uppercase letters. The $i$-th letter of each of these strings is the letter on the $i$-th block from the bottom in the represented tower.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is a string representing a valid megatower as described above, or the word IMPOSSIBLE if no valid megatower can be built. (Notice that the string IMPOSSIBLE can never itself represent a valid megatower, since the two $\mathbf{i}$ s have other letters in between.)

## 样例

### 样例输入 1
```
6
5
CODE JAM MIC EEL ZZZZZ
6
CODE JAM MIC EEL ZZZZZ EEK
2
OY YO
2
HASH CODE
6
A AA BB A BA BB
2
CAT TAX
```

### 样例输出 1
```
Case #1: ZZZZZJAMMICCODEEEL
Case #2: IMPOSSIBLE
Case #3: IMPOSSIBLE
Case #4: IMPOSSIBLE
Case #5: BBBBBAAAAA
Case #6: IMPOSSIBLE
```

## 提示

**Sample Explanation 1**

In Sample Case #1, `JAMMICCODEEELZZZZZ` and `ZZZZZJAMMICCODEEEL` are the only two valid outputs.

In Sample Case #2, recall that all towers must be used in the megatower, so even though the first five towers together would form a valid megatower (as in Sample Case #1), the additional `EEK` makes the case impossible. No matter how the `EEL` and `EEK` towers are stacked relative to each other, there will be at least two non-contiguous groups of `E`s.

In Sample Case #3, no matter how you stack the towers, either the two `O`s are not contiguous or the two Ys are not contiguous.

In Sample Case #4, there are non-H letters in between the `H`s of `HASH`, so this case is also impossible.

In Sample Case #5, this answer is the only valid one. Also notice that the towers are not necessarily all distinct.

In Sample Case #6, no matter how you stack the towers, the two `A`s cannot be contiguous.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \text{the length of } \mathbf{S}_i \leq 10$, for all $i$.

**Test Set 1 (10 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 6$.

**Test Set 2 (15 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 100$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;

        vector<string> towers(n);
        for (int i = 0; i < n; i++) cin >> towers[i];

        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;

        bool found = false;
        string result;

        do {
            string megatower;
            for (int i : order) megatower += towers[i];

            bool valid = true;
            for (char c = 'A'; c <= 'Z'; c++) {
                int first = -1, last = -1;
                for (int i = 0; i < (int)megatower.size(); i++) {
                    if (megatower[i] == c) {
                        if (first == -1) first = i;
                        last = i;
                    }
                }
                if (first != -1) {
                    for (int i = first; i <= last; i++) {
                        if (megatower[i] != c) {
                            valid = false;
                            break;
                        }
                    }
                }
                if (!valid) break;
            }

            if (valid) {
                result = megatower;
                found = true;
                break;
            }
        } while (next_permutation(order.begin(), order.end()));

        cout << "Case #" << t << ": ";
        if (found) cout << result << "\n";
        else cout << "IMPOSSIBLE\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
给定 N 个字母积木塔（每个塔是一个字符串），需要将它们按某种顺序堆叠成一个"超级塔"，使得每种字母在超级塔中连续出现（即同一种字母不能被其他字母隔开）。如果存在合法排列则输出，否则输出 IMPOSSIBLE。

### 核心思路
暴力枚举所有塔的排列顺序，对每种排列拼接成超级塔后验证合法性。由于题目限制 N ≤ 100，但每种测试用例的积木字符串长度 ≤ 10，实际可行。

### 算法流程
1. 读入 N 个塔的字符串
2. 生成塔下标的所有全排列
3. 对每种排列，按顺序拼接所有字符串形成超级塔
4. 对超级塔进行合法性检查：对 'A' 到 'Z' 的每个字母，找到其首次和末次出现的位置，检查这段区间内是否全为该字母
5. 若找到合法排列则输出结果并停止；若所有排列都不合法则输出 IMPOSSIBLE

### 复杂度分析
- 时间复杂度：O(N! × N × L)，其中 N 为塔数，L 为拼接后超级塔的总长度（最多 100×10=1000），全排列枚举为 O(N!)
- 空间复杂度：O(N × L)，存储所有塔和拼接结果
