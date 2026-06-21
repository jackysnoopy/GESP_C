# [GCJ 2008 Qualification] Train Timetable

## 题目描述

一条铁路上有两个车站 A 和 B，列车可在 A、B 之间往返。列车到达对方站后需要 **turnaround（周转）时间** T 分钟准备才能发车返程。给出当日所有车次的时刻表（A→B 和 B→A 各若干趟，含发车、到达时间），问：为使时刻表正常运转，分别需要在 A、B 各停放多少列车作为始发车？只要有车次按时刻表发车，对应车站就必须有一辆车待命。轨道有会让线，列车到达顺序不必与发车顺序一致。

## 输入格式

第一行整数 N 为数据组数。每组数据：
- 第一行：周转时间 T（分钟）。
- 第二行：两个整数 N_A、N_B，分别为 A→B、B→A 的车次数。
- 随后 N_A 行，每行 `HH:MM HH:MM` 表示 A→B 的发车与到达时间。
- 随后 N_B 行，每行 `HH:MM HH:MM` 表示 B→A 的发车与到达时间。

时间在当天 00:00–23:59，发车早于到达，车次顺序未排序。

## 输出格式

每组数据输出一行 `Case #x: a b`，其中 a、b 分别为必须在 A、B 始发的列车数。

## 提示

约束：小数据 N≤20、N_A,N_B≤20、T≤5；大数据 N≤100、N_A,N_B≤100、T≤60。

## 解题思路

### 问题分析

关键在于一辆执行完一趟的车，到达对方站后经周转可被"返程车次"复用，从而减少需要新购的始发车。把 A→B 与 B→A 两类车次按发车时间统一排序后贪心调度即可：对每个发车车次，优先复用本站最早可用的车，否则才需新增一辆始发车。

### 核心思路

维护两个小根堆 `availA`、`availB`，分别存 A、B 两站"已就绪可发车"的时刻（= 到达时刻 + 周转 T）。
- 将 A→B、B→A 车次按发车时间升序合并处理。
- 对一趟 A→B 车次（发车 d、到达 a）：若 `availA` 顶部 ≤ d，说明本站有车就绪，复用（弹出）；否则 `ca++` 新增始发车。该车到达 B 后经周转可服务返程，把 `a + T` 压入 `availB`。
- 对一趟 B→A 车次对称处理：复用 `availB` 否则 `cb++`，并把 `a + T` 压入 `availA`。
- 由于只需统计"是否需要新增始发车"，复用最早就绪的车是最优且无后效性的贪心。

### 算法流程

1. 读入 T 与每组数据，把 `HH:MM` 转为分钟数。
2. 分别对 A→B、B→A 车次按发车时间排序。
3. 用双指针 ia、ib 按发车时间合并两类车次。
4. 对每趟车次按上述规则复用或新增，并更新对应站点的就绪堆。
5. 输出 `Case #x: ca cb`。

### 复杂度分析

车次总数 M = N_A + N_B。排序 O(M log M)，堆操作 O(M log M)。总体 O(M log M)，对 M ≤ 200 足够。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int toMin(const string& s) {
    return ((s[0]-'0')*10 + (s[1]-'0')) * 60 + (s[3]-'0')*10 + (s[4]-'0');
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int turnaround;
        cin >> turnaround;
        int NA, NB;
        cin >> NA >> NB;
        vector<pair<int,int>> A, B;
        for (int i = 0; i < NA; i++) {
            string s, e; cin >> s >> e;
            A.push_back({toMin(s), toMin(e)});
        }
        for (int i = 0; i < NB; i++) {
            string s, e; cin >> s >> e;
            B.push_back({toMin(s), toMin(e)});
        }
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        // availA / availB: earliest ready time of a train waiting at A / B
        priority_queue<int, vector<int>, greater<int>> availA, availB;
        int ca = 0, cb = 0;
        int ia = 0, ib = 0;
        while (ia < (int)A.size() || ib < (int)B.size()) {
            bool takeA;
            if (ia >= (int)A.size()) takeA = false;
            else if (ib >= (int)B.size()) takeA = true;
            else takeA = (A[ia].first <= B[ib].first);
            if (takeA) {
                int d = A[ia].first, a = A[ia].second; ia++;
                if (!availA.empty() && availA.top() <= d) availA.pop();
                else ca++;
                availB.push(a + turnaround);
            } else {
                int d = B[ib].first, a = B[ib].second; ib++;
                if (!availB.empty() && availB.top() <= d) availB.pop();
                else cb++;
                availA.push(a + turnaround);
            }
        }
        cout << "Case #" << tc << ": " << ca << " " << cb << "\n";
    }
    return 0;
}
```
