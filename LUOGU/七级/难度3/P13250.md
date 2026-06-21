# [GCJ 2014 #1B] The Repeater

## 题目描述

Fegla 和 Omar 玩一个新游戏 "The Repeater"。Fegla 写下 N 个字符串，Omar 要用最少操作把它们变成完全相同。每次操作可选其一：

1. 选任意一个字符，在其后**重复插入一个相同字符**（如 `abc` -> `abbc`，重复 `b`）。
2. 选任意两个相邻且相同的字符，**删除其中一个**（如 `abbc` -> `abc`，但不能再删成 `bbc`）。

两种操作互相独立。若无法让所有字符串相同，则 Omar 失败。

## 输入格式

第一行一个整数 T，表示测试数据组数。
每组数据第一行一个整数 N，表示字符串个数；随后 N 行，每行一个由小写字母组成的非空字符串。

## 输出格式

每组数据输出一行 `Case #x: y`，其中 x 为数据编号（从 1 开始），y 为最少操作次数；若不可能则输出 `Fegla Won`。

## 提示

约束：
- 1 ≤ T ≤ 100，1 ≤ 字符串长度 ≤ 100。
- 小数据 N = 2；大数据 2 ≤ N ≤ 100。

## 解题思路

### 问题分析

每次操作只能在"同一段连续相同字符"内部增删一个字符，无法改变字符的种类或顺序。因此能否成功，取决于各字符串的"压缩骨架"是否一致；若一致，则把每一段的长度对齐到某个目标值即可，代价为各长度到目标值之差的绝对值之和。

### 核心思路

对每个字符串做游程编码（Run-Length Encoding），得到形如 `(字符, 连续个数)` 的序列。
- **可行性**：所有字符串的 RLE 必须长度相同，且对应位置的字符相同；否则输出 `Fegla Won`。
- **最优性**：对每个位置 j，设各字符串该段长度为 c_1..c_N，需选一个目标长度 t 使 sum|c_i - t| 最小。使该式最小的 t 即为这组数的**中位数**（取排序后第 N/2 个），代价为各数到中位数的绝对差之和。
- 总答案为所有位置代价之和。

### 算法流程

1. 读入 T，对每组数据读入 N 个字符串。
2. 对每个字符串做游程编码 `rle(s)`：遍历字符，遇新字符就新开一段，否则给当前段计数 +1。
3. 检查可行性：所有 RLE 长度相同，且逐位字符相同。
4. 若不可行输出 `Fegla Won`；否则对每个位置收集 N 个计数，排序取中位数，累加 |c_i - 中位数|。
5. 输出 `Case #x: 总代价`。

### 复杂度分析

设字符串长度为 L、字符串数为 N。游程编码 O(L)，逐位对齐 O(N·L)，排序取中位数 O(N log N) 每位。总体 O(N·L·log N)，对 N,L ≤ 100 完全足够。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<pair<char,int>> rle(const string& s) {
    vector<pair<char,int>> r;
    for (char c : s) {
        if (r.empty() || r.back().first != c) r.push_back({c, 1});
        else r.back().second++;
    }
    return r;
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<string> s(N);
        for (int i = 0; i < N; i++) cin >> s[i];
        vector<vector<pair<char,int>>> enc(N);
        for (int i = 0; i < N; i++) enc[i] = rle(s[i]);
        bool ok = true;
        int len = enc[0].size();
        for (int i = 1; i < N; i++)
            if ((int)enc[i].size() != len) ok = false;
        if (ok) {
            for (int j = 0; j < len; j++)
                for (int i = 1; i < N; i++)
                    if (enc[i][j].first != enc[0][j].first) ok = false;
        }
        cout << "Case #" << tc << ": ";
        if (!ok) { cout << "Fegla Won\n"; continue; }
        int ans = 0;
        for (int j = 0; j < len; j++) {
            vector<int> cnts;
            for (int i = 0; i < N; i++) cnts.push_back(enc[i][j].second);
            sort(cnts.begin(), cnts.end());
            int med = cnts[N / 2];
            for (int v : cnts) ans += abs(v - med);
        }
        cout << ans << "\n";
    }
    return 0;
}
```
