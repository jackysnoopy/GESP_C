# [GCJ 2014 #3] Crime House

## 题目描述

监控 Crime House 的进出记录，部分人戴面具（id=0）。判断是否没有其他出入口，并求最终最少人数。

## 输入格式

第一行 T，每组包含 N 条记录（E/L + id）。

## 输出格式

Case #x: y，y 为最少人数或 CRIME TIME。

## 样例

```
5
3
E 5
L 0
E 5
...
```

输出：
```
Case #1: 1
Case #2: CRIME TIME
```

## 解题思路

### 问题分析
关键：面具人的进出可以匹配任何已知人的进出。需要判断是否存在合法匹配使得总人数最小。

### 核心思路
- 贪心模拟：面具人进入时，优先匹配已在屋内的人；面具人离开时，优先减少计数
- 跟踪已知人在屋内的状态和面具人的净进出

### 算法流程
1. 维护已知人在屋内的计数
2. 面具人进入：若有人在屋内，匹配之（减少计数）；否则增加新人口
3. 面具人离开：若有人在屋内，匹配之；否则必须有之前面具人进入匹配
4. 违法则输出 CRIME TIME

### 复杂度分析
- 时间：O(N)
- 空间：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N; cin >> N;
        vector<pair<string,int>> events(N);
        for (int i = 0; i < N; i++) cin >> events[i].first >> events[i].second;
        cout << "Case #" << t << ": ";
        map<int,int> inside; int inside_count = 0, min_people = 0;
        bool possible = true;
        for (int i = 0; i < N && possible; i++) {
            string type = events[i].first; int id = events[i].second;
            if (type == "E") {
                if (id == 0) { if (inside_count > 0) inside_count--; else min_people++; }
                else { inside[id]++; inside_count++; }
            } else {
                if (id == 0) { if (inside_count > 0) inside_count--; else { min_people--; if (min_people < 0) possible = false; } }
                else { if (inside[id] > 0) { inside[id]--; inside_count--; } else possible = false; }
            }
        }
        if (!possible) cout << "CRIME TIME\n";
        else { int rem = 0; for (auto& p : inside) rem += p.second; cout << rem << "\n"; }
    }
    return 0;
}
```
