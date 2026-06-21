# 团体队列 Team Queue

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=481

[PDF](https://uva.onlinejudge.org/external/5/p540.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA540/0c38a6f278cc1600f2c302c4e62e49849580b4a0.png)

## 输入格式
![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA540/45f48a6372d0dfd77f687471a8371c7c392d6e67.png)

## 输出格式
![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA540/df33e580d1ac771499f7930294a5c07a5ee10625.png)

## 样例
### 样例 1
```
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
2
5 259001 259002 259003 259004 259005
6 260001 260002 260003 260004 260005 260006
ENQUEUE 259001
ENQUEUE 260001
ENQUEUE 259002
ENQUEUE 259003
ENQUEUE 259004
ENQUEUE 259005
DEQUEUE
DEQUEUE
ENQUEUE 260002
ENQUEUE 260003
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0
```
```
Scenario #1
101
102
103
201
202
203

Scenario #2
259001
259002
259003
259004
259005
260001
```

## 解题思路
### 问题分析
多队列排队模拟。每个元素属于一个团队，新元素插到所属团队在队列的末尾。

### 核心思路
用主队列存团队编号，每个团队有自己的队列。

### 算法流程
1. 读入团队数和成员
2. ENQUEUE x：若团队在主队列中，加入团队队列；否则团队入主队列
3. DEQUEUE：输出主队列队首团队的队首元素，若团队队列为空则出主队列

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

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
