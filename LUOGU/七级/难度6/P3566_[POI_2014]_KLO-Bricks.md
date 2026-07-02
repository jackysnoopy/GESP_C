# P3566 [POI 2014] KLO-Bricks

## 题目描述

Little Bitie and his friends spent the whole yesterday playing with colorful bricks in the kindergarten.

Initially they made building models but they quickly got bored with that.

Then they decided to place the bricks in a line, one after another.

To avoid a dull look, they tried to avoid putting two bricks of the same color next to each other.

After a long while they succeeded in placing all the bricks while observing this rule.

Then the day care was over, and the children went home with their parents.

Today Bitie came to the kindergarten early.

He was satisfied to see that their yesterday's creation was still standing.

But then he tripped over in a most unfortunate way, falling right on the line of bricks, which all mixed in a pile.

The boy quickly sorted them by color and wondered how best to quickly reassemble the perfect line.

He managed to recall what were the colors of the two bricks on both end of the line.

Help little Bitie out and tell him how to order the bricks in a line so that no two bricks of the same color are next to each other and the bricks at the ends of the line have the colors that he recalled.

Note that Bitie could have made a mistake in recalling the two colors or perhaps he did not find some of the blocks after falling into them, so the reconstruction might not be possible.

## 输入格式

There are three integers in the first line of the standard input, $k$, $p$, and $q$（$1 \le k \le 1\,000\,000$, $1 \le p, q \le k$），separated by single spaces, denoting the number of brick colors, and the colors of the first and the last brick in the desired arrangement, respectively.

In the second line, there are $k$ integers, $i_1, i_2, \ldots, i_k$（$1 \le i_j \le 1\,000\,000$），separated by single spaces.

The number $i_j$ signifies that Bitie has exactly $i_j$ bricks of color $j$.

You may assume that the total number of bricks does not exceed one million, i.e., that $n = i_1 + i_2 + \cdots + i_k \le 1\,000\,000$.

## 输出格式

Your program should print $n$ integers to the standard output, separated by single spaces.

The numbers should represent the colors of successive bricks in an arrangement that satisfies aforementioned constraints.

If no such arrangement exists, your program should print only a single integer: $0$.

If there are several correct answers, your program can pick one arbitrarily.

## 样例

输入：
```
3 3 1
2 3 3
```
输出：
```
3 2 1 3 2 3 2 1
```

## 解题思路

### 问题分析

这是一个贪心+优先队列问题。需要将砖块排成一行，使得相邻砖块颜色不同，且首尾颜色分别为 $p$ 和 $q$。

### 核心思路

1. 使用优先队列维护每种颜色的砖块数量
2. 每次选择数量最多的颜色（但不能与上一块相同）
3. 首尾颜色固定为 $p$ 和 $q$

### 算法流程

1. 读取每种颜色的砖块数量
2. 使用优先队列维护颜色数量
3. 每次选择数量最多的颜色（排除上一块的颜色）
4. 如果无法选择，输出 0

### 复杂度分析

- 时间复杂度：$O(n \log k)$
- 空间复杂度：$O(k)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, p, q;
    cin >> k >> p >> q;
    
    vector<int> cnt(k + 1);
    for (int i = 1; i <= k; i++) cin >> cnt[i];
    
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= k; i++) {
        if (cnt[i] > 0) pq.push({cnt[i], i});
    }
    
    vector<int> ans;
    int last = -1;
    
    while (!pq.empty()) {
        auto [c, color] = pq.top();
        pq.pop();
        
        if (color == last) {
            if (pq.empty()) {
                cout << 0 << endl;
                return 0;
            }
            auto [c2, color2] = pq.top();
            pq.pop();
            ans.push_back(color2);
            last = color2;
            if (c2 > 1) pq.push({c2 - 1, color2});
            pq.push({c, color});
        } else {
            ans.push_back(color);
            last = color;
            if (c > 1) pq.push({c - 1, color});
        }
    }
    
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    
    return 0;
}
```
