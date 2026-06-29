# Cinema

## 题目描述

有 n 位观众，每位观众会说一种语言。现在有 m 部电影，每部电影有配音语言 audio 和字幕语言 sub。选择一部电影使得最多观众能听懂配音（优先），在配音语言相同的条件下，最多观众能看懂字幕。

## 输入格式

- 第一行一个整数 n
- 第二行 n 个整数，表示每位观众会说的语言
- 第三行一个整数 m
- 第四行 m 个整数，表示每部电影的配音语言
- 第五行 m 个整数，表示每部电影的字幕语言

## 输出格式

输出最优电影的编号（从 1 开始）

## 样例

```
输入：
7
3 2 2 1 2 1 1
2
1 2
1 2

输出：
1
```

## 提示

- 使用 map 统计每种语言的观众数量
- 遍历所有电影，选择最优的

## 解题思路

### 问题分析

需要在 m 部电影中选择一部，使得听懂配音的观众最多，其次看懂字幕的观众最多。

### 核心思路

使用 map 统计每种语言的观众数量。遍历每部电影，计算其配音语言和字幕语言对应的观众数量，选择最优的。

### 算法流程

1. 统计每种语言的观众数量 cnt[lang]
2. 遍历每部电影 i：
   - 计算 a = cnt[audio[i]]，s = cnt[sub[i]]
   - 若 a > best_audio 或 (a == best_audio 且 s > best_sub)，更新最优解
3. 输出最优电影的编号

### 复杂度分析

- 时间复杂度：O(n + m)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int lang;
        cin >> lang;
        cnt[lang]++;
    }
    
    int m;
    cin >> m;
    vector<int> audio(m), sub(m);
    for (int i = 0; i < m; i++) cin >> audio[i];
    for (int i = 0; i < m; i++) cin >> sub[i];
    
    int best_idx = 0, best_audio = -1, best_sub = -1;
    for (int i = 0; i < m; i++) {
        int a = cnt[audio[i]];
        int s = cnt[sub[i]];
        if (a > best_audio || (a == best_audio && s > best_sub)) {
            best_audio = a;
            best_sub = s;
            best_idx = i + 1;
        }
    }
    
    cout << best_idx << "\n";
    return 0;
}
```
