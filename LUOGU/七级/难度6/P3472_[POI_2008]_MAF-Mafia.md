# P3472 [POI 2008] MAF-Mafia

## 题目描述

Mob feud rages in Equatorial Byteotia. The mob bosses have come to the country's capital, Byteburg, to settle the dispute.

Negotiations were very tense, and at one point the trigger-happy participants drew their guns.

Each participant aims at another with a pistol.

Should they go on a killing spree, the shooting will go in accordance with the following code of honour:

the participants shoot in a certain order, and at any moment at most one of them is shooting, no shooter misses, his target dies instantly, hence he may not shoot afterwards, everyone shoots once, provided he had not been shot before he has a chance to shoot, no participant may change his first target of choice, even if the target is already dead (then the shot causes no further casualties).

An undertaker watches from afar, as he usually does. After all, the mobsters have never failed to stimulate his business.

He sees potential profit in the shooting, but he would like to know tight estimations. Precisely he would like to know the minimum and maximum possible death rate.

The undertaker sees who aims at whom, but does not know the order of shooting.

You are to write a programme that determines the numbers he is so keen to know.

## 输入格式

第一行包含参与者数量 $n$（$1 \le n \le 1\,000\,000$）。

他们编号从 $1$ 到 $n$。

第二行包含 $n$ 个整数 $s_1, s_2, \cdots, s_n$，用空格分隔，$1 \le s_i \le n$。

$s_i$ 表示第 $i$ 个参与者的目标编号。

注意，对于某些 $i$，可能 $s_i = i$（紧张，你知道的）。

## 输出格式

你的程序应该在标准输出的第一行（也是唯一一行）中输出两个整数，用单个空格分隔。这些数字应该是射击造成的最小和最大伤亡人数。

## 样例

输入：
```
8
2 3 2 2 6 7 8 5
```
输出：
```
3 5
```

## 解题思路

### 问题分析

这是一个图论问题。需要分析有向图中的环和链结构。

### 核心思路

1. 将问题转化为有向图
2. 找出所有的环和链
3. 对于环，最小伤亡为 $\lfloor n/2 \rfloor$，最大伤亡为 $n$
4. 对于链，最小伤亡为 0，最大伤亡为链长

### 算法流程

1. 构建有向图
2. 使用DFS找出所有的环和链
3. 计算最小和最大伤亡人数

### 复杂度分析

- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

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
    
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        s[i]--;
    }
    
    vector<int> vis(n, 0);
    int min_ans = 0, max_ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        
        int u = i;
        while (!vis[u]) {
            vis[u] = i + 1;
            u = s[u];
        }
        
        if (vis[u] == i + 1) {
            int cycle_len = 0;
            int v = u;
            do {
                cycle_len++;
                v = s[v];
            } while (v != u);
            
            min_ans += cycle_len / 2;
            max_ans += cycle_len;
        }
    }
    
    cout << min_ans << " " << max_ans << endl;
    return 0;
}
```
