# Mountain Climbing

## 题目描述

约翰农夫发现他的奶牛在进行剧烈运动时会产出更高质量的牛奶。因此，他决定让他的 $N$ 头奶牛（$1 \le N \le 25,000$）去爬一座附近的山，然后再下来！

第 $i$ 头奶牛需要 $U(i)$ 的时间爬上山，然后需要 $D(i)$ 的时间爬下山。由于奶牛是家养的，每头奶牛在爬山的每一段路程中都需要农夫的帮助，但由于经济不景气，只有两位农夫可用，即约翰农夫和他的表弟唐农夫。约翰农夫计划指导奶牛上山，而唐农夫将指导奶牛下山。由于每头奶牛都需要一个向导，并且每段旅程中只有一位农夫，因此在任何时间点，最多只有一头奶牛可以在约翰农夫的帮助下爬上山，最多只有一头奶牛可以在唐农夫的帮助下爬下山。奶牛可能会在山顶暂时聚集，如果它们爬上山后需要等待唐农夫的帮助才能下山。奶牛下山的顺序可以与上山的顺序不同。

请确定所有 $N$ 头奶牛完成整个旅程所需的最短时间。

## 输入格式

第一行，一个整数 $N$。

第 $2$ 到第 $N+1$ 行，每行两个用空格隔开的整数 $U(i)$ 和 $D(i)$。

$(1 \le U(i),D(i) \le 50,000)$。

## 输出格式

一行一个整数，表示所有 $N$ 头奶牛完成旅程的最短时间。

## 样例

### 样例1
输入：
```
3
6 4
8 1
2 3
```
输出：
```
17
```

## 提示

- $1 \le N \le 25,000$
- $1 \le U(i), D(i) \le 50,000$

## 解题思路

### 问题分析

这是一个经典的调度问题，涉及两个阶段（上山和下山）以及两个执行者（约翰农夫和唐农夫）。每头奶牛需要先上山再下山，但上山和下山可以由不同的农夫完成。

### 核心思路

1. **贪心策略**：按照上山时间从大到小排序
2. **双线程调度**：维护两个时间变量，分别记录约翰农夫和唐农夫的当前时间
3. **最优匹配**：每次选择当前空闲的农夫，如果两个都空闲，优先选择能更快完成的方案

### 算法流程

1. 读入所有奶牛的上山和下山时间
2. 按照上山时间从大到小排序
3. 遍历每头奶牛：
   - 如果约翰农夫的时间小于等于唐农夫的时间，让约翰农夫先上山
   - 否则让唐农夫先下山
   - 更新两个农夫的时间
4. 输出两个时间中的较大值

### 复杂度分析

- 时间复杂度：$O(N \log N)$，主要来自排序
- 空间复杂度：$O(N)$，存储奶牛信息

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow {
    int up, down;
};

bool cmp(const Cow& a, const Cow& b) {
    return a.up > b.up;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].up >> cows[i].down;
    }
    
    sort(cows.begin(), cows.end(), cmp);
    
    int time_fj = 0, time_fd = 0;
    for (int i = 0; i < n; i++) {
        if (time_fj <= time_fd) {
            time_fj += cows[i].up;
            time_fd = max(time_fd, time_fj) + cows[i].down;
        } else {
            time_fd += cows[i].down;
            time_fj = max(time_fj, time_fd) + cows[i].up;
        }
    }
    
    cout << max(time_fj, time_fd) << endl;
    
    return 0;
}
```
