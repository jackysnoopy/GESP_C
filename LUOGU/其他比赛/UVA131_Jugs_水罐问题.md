# UVA131 - Jugs (水罐问题)

## 题目描述

有两个水罐，容量分别为A和B（A < B）。目标是在B罐中测量出恰好D升水。可以执行以下操作：
1. 从水龙头装满任一罐子
2. 倒空任一罐子到地面
3. 将一个罐子中的水倒入另一个罐子

## 算法思路

1. 使用BFS搜索状态空间
2. 状态表示为(a, b)，表示两个罐子中的水量
3. 每次扩展六种可能的操作
4. 使用map记录访问过的状态避免重复
5. 找到目标状态后输出操作序列

## 复杂度分析

- 时间复杂度：O(A × B)，最多访问A×B个状态
- 空间复杂度：O(A × B)，存储访问状态和操作序列

## C++ 代码

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct State {
    int a, b;
    string ops;
};

int main() {
    int A, B, D;
    while (cin >> A >> B >> D) {
        queue<State> q;
        map<pair<int,int>, bool> visited;
        q.push({0, 0, ""});
        visited[{0, 0}] = true;
        while (!q.empty()) {
            State cur = q.front(); q.pop();
            if (cur.b == D) {
                cout << cur.ops;
                break;
            }
            if (cur.a < A && !visited[{A, cur.b}]) {
                visited[{A, cur.b}] = true;
                q.push({A, cur.b, cur.ops + "fill A\n"});
            }
            if (cur.b < B && !visited[{cur.a, B}]) {
                visited[{cur.a, B}] = true;
                q.push({cur.a, B, cur.ops + "fill B\n"});
            }
            if (cur.a > 0 && !visited[{0, cur.b}]) {
                visited[{0, cur.b}] = true;
                q.push({0, cur.b, cur.ops + "empty A\n"});
            }
            if (cur.b > 0 && !visited[{cur.a, 0}]) {
                visited[{cur.a, 0}] = true;
                q.push({cur.a, 0, cur.ops + "empty B\n"});
            }
            if (cur.a > 0 && cur.b < B) {
                int pour = min(cur.a, B - cur.b);
                int na = cur.a - pour, nb = cur.b + pour;
                if (!visited[{na, nb}]) {
                    visited[{na, nb}] = true;
                    q.push({na, nb, cur.ops + "pour A B\n"});
                }
            }
            if (cur.b > 0 && cur.a < A) {
                int pour = min(cur.b, A - cur.a);
                int na = cur.a + pour, nb = cur.b - pour;
                if (!visited[{na, nb}]) {
                    visited[{na, nb}] = true;
                    q.push({na, nb, cur.ops + "pour B A\n"});
                }
            }
        }
    }
    return 0;
}
```

## 样例输入输出

输入：
```
3 5 4
```

输出：
```
fill B
pour B A
empty A
pour B A
fill B
pour B A
```

解释：通过一系列操作，在B罐中测量出4升水。
