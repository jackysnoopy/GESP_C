# Gym Badges

## 题目描述

你是一只初始等级为 $0$ 的 $\text{Wabbit}$。你希望到 $N$ 个比赛中提升自己的实力，并收集这些比赛的徽章。

目前将要举行的比赛共有 $N$ 个。第 $i$ 个比赛可以用 $L_i$ 和 $X_i$ 来描述。如果你的当前等级 $\le L_i$，那么你可以参加第 $i$ 个比赛，让自己的等级提升 $X_i$ 并获得一个徽章。

你可以以任意顺序参加这些比赛。求出如果按照最佳顺序参加，你最多可以获得多少个徽章。

## 输入格式

第一行，一个正整数 $N$；

第二行 $N$ 个整数，表示 $X_i$。

第三行 $N$ 个整数，表示 $L_i$。

## 输出格式

一行一个整数，表示最多能收集到的徽章个数。

## 样例

### 样例输入

```
5
4 6 3 5 2
10 6 4 8 12
```

### 样例输出

```
4
```

### 样例输入

```
5
3 9 4 2 6
10 10 10 10 10
```

### 样例输出

```
4
```

## 提示

### 样例解释

样例1：一种最优的参加方式为 $3 \to 4 \to 1 \to 5$。

样例2：一种最优的参加方式为 $1 \to 3 \to 4 \to 2$。

### 数据范围

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$15$|$1\le N\le10$|
|$2$|$9$|所有 $L_i$ 均相等|
|$3$|$27$|$1\le N\le5000$|
|$4$|$49$|无|

对于 $100\%$ 的数据，$1 \le N \le 5 \times 10 ^ 5, 1 \le X_i, L_i \le 10 ^ 9$。

## 解题思路

### 问题分析

这是一个贪心问题。我们需要选择比赛的参加顺序，使得能参加的比赛数量最多。

关键点：
1. 初始等级为0
2. 每个比赛有等级要求 $L_i$ 和等级提升 $X_i$
3. 只有当前等级 $\le L_i$ 时才能参加比赛
4. 参加比赛后等级提升 $X_i$

### 核心思路

1. **排序策略**：按照比赛的要求等级 $L_i$ 从小到大排序。
2. **贪心选择**：对于相同等级要求的比赛，优先选择等级提升 $X_i$ 较小的比赛。
3. **理由**：选择 $X_i$ 较小的比赛可以保持较低的等级，从而能参加更多后续比赛。

### 算法流程

1. 将比赛按照 $L_i$ 排序。
2. 初始化当前等级为0，计数器为0。
3. 遍历排序后的比赛：
   - 如果当前等级 $\le L_i$，则参加该比赛，等级提升 $X_i$，计数器加1。
4. 输出计数器的值。

### 复杂度分析

- 时间复杂度：$O(n \log n)$，主要是排序的时间复杂度。
- 空间复杂度：$O(n)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5e5 + 10;

int n;
int X[MAXN], L[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> X[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> L[i];
    }
    
    // 将比赛按照L[i]排序
    vector<pair<int, int>> competitions;
    for (int i = 1; i <= n; i++) {
        competitions.push_back({L[i], X[i]});
    }
    sort(competitions.begin(), competitions.end());
    
    // 贪心：每次选择能参加的比赛中X[i]最小的
    long long currentLevel = 0;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentLevel <= competitions[i].first) {
            currentLevel += competitions[i].second;
            count++;
        }
    }
    
    cout << count << '\n';
    
    return 0;
}
```