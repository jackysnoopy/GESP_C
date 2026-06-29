# Team Queue

## 题目描述

有 t 个团队的人排队，每个人属于某个团队。当一个人入队时，如果他的团队已经在队列中，则排在该团队最后一个人后面；否则排在整个队列最后。出队时从队首出队。支持 ENQUEUE、DEQUEUE 和 STOP 操作。

## 输入格式

- 多组测试数据，每组第一行一个整数 t（团队数）
- 每个团队先输入成员数 n，然后 n 个成员编号
- 接下来是操作序列，以 STOP 结束

## 输出格式

对于每个 DEQUEUE 操作，输出出队的成员编号。每组数据后输出一个空行。

## 样例

```
输入：
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0

输出：
Scenario #1
101
102
103
201
202
203

```

## 提示

- 使用队列的队列：主队列存储团队编号，每个团队有自己的子队列
- 入队时检查该团队是否已在主队列中

## 解题思路

### 问题分析

需要实现一个特殊的队列，支持团队级别的排队规则。

### 核心思路

使用两层队列结构：
- 主队列：存储团队编号，表示团队的排队顺序
- 子队列：每个团队一个队列，存储该团队的成员
- 使用 in_main 标记每个团队是否已在主队列中

### 算法流程

1. ENQUEUE x：
   - 找到 x 所属团队 tid
   - 将 x 加入 team_q[tid]
   - 若 tid 不在主队列中，将 tid 加入主队列
2. DEQUEUE：
   - 从主队列队首取出团队 tid
   - 输出 team_q[tid] 的队首元素
   - 若 team_q[tid] 为空，从主队列中移除 tid
3. STOP：结束当前测试数据

### 复杂度分析

- 时间复杂度：O(总操作数)
- 空间复杂度：O(总人数)

## 参考代码

```cpp
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, cas = 0;
    while (cin >> t && t) {
        cout << "Scenario #" << ++cas << "\n";
        map<int, int> team_of;
        for (int i = 0; i < t; i++) {
            int n; cin >> n;
            while (n--) { int x; cin >> x; team_of[x] = i; }
        }
        
        queue<int> main_q;
        vector<queue<int>> team_q(t);
        vector<bool> in_main(t, false);
        
        string op;
        while (cin >> op && op != "STOP") {
            if (op == "ENQUEUE") {
                int x; cin >> x;
                int tid = team_of[x];
                team_q[tid].push(x);
                if (!in_main[tid]) {
                    main_q.push(tid);
                    in_main[tid] = true;
                }
            } else {
                int tid = main_q.front();
                cout << team_q[tid].front() << "\n";
                team_q[tid].pop();
                if (team_q[tid].empty()) {
                    main_q.pop();
                    in_main[tid] = false;
                }
            }
        }
        cout << "\n";
    }
    return 0;
}
```
