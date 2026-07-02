# 「HGOI-1」Mole

## 题目描述
在长度为 $l$ 的游戏窗口上，有一个长为 $t$ 的地鼠序列 $(l \le t)$，初始序列左端与窗口左端对齐，接下来序列每秒移动一个单位长度，向左滚动直至玩家结束游戏或者序列最右端与窗口最右端重合。

游戏开始的第一秒序列不会移动，不难发现游戏最多会进行 $(t-l+1)$ 秒。

序列 $T$ 中的每一只地鼠都有自己的高度 $h_i$，玩家每次可以选择击打一只地鼠，玩家可以获得与地鼠高度 $h_i$ 数值相同的金币奖励，同时地鼠 $i$ 的高度 $h_i$ 会减一。

经过调研，$\text{brealid}$ 控制了游戏运行速度，使得玩家在地鼠序列移动一个单位长度的同时最多只能打击一次（也可以不打）。

现在 $\text{brealid}$ 告诉了你某一次游戏的窗口长度 $l$、序列长度 $t$ 以及某一局游戏中生成的地鼠高度序列 $T$。我们可爱的 $\text{brealid}$ 想要知道，她在任意时刻结束游戏所能得到的最多金币。

## 输入格式
第一行两个整数 $l$，$t$，表示窗口长度 $l$ 和序列长度 $t$。

第二行 $t$ 个整数，表示某一局中的地鼠高度序列。

## 输出格式
一行 $t-l+1$ 个整数 $a_1,a_2,\cdots a_{t-l+1}$，$a_i$ 表示第 $i$ 秒时结束游戏可以获得的最多的金币数。

## 样例
### 样例1
输入:
```
5 10
1 3 1 1 1 1 1 1 5 1
```
输出:
```
3 5 6 7 12 16
```

## 提示
- 时间限制：1000ms
- 内存限制：131072KB

## 解题思路

### 问题分析
滑动窗口问题，每次窗口移动时可以选择击打一个地鼠。

### 核心思路
1. 使用优先队列维护当前窗口内地鼠高度
2. 每次移动窗口时，更新优先队列
3. 贪心选择最高的地鼠击打

### 算法流程
1. 初始化第一个窗口的优先队列
2. 每次移动窗口：移除最左边的地鼠，添加新的地鼠
3. 在每个时刻计算最大金币数

### 复杂度分析
- 时间复杂度：$O(t \log l)$
- 空间复杂度：$O(l)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000005;
int h[MAXN];
int l, t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> l >> t;
    
    for (int i = 0; i < t; i++) {
        cin >> h[i];
    }
    
    vector<int> ans;
    
    for (int start = 0; start <= t - l; start++) {
        priority_queue<int> pq;
        
        for (int i = start; i < start + l; i++) {
            if (h[i] > 0) {
                pq.push(h[i]);
            }
        }
        
        int total = 0;
        int hits = 0;
        
        while (!pq.empty() && hits < l) {
            int top = pq.top();
            pq.pop();
            
            total += top;
            hits++;
            
            if (top - 1 > 0) {
                pq.push(top - 1);
            }
        }
        
        ans.push_back(total);
    }
    
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i + 1 == ans.size() ? "\n" : " ");
    }
    
    return 0;
}
```