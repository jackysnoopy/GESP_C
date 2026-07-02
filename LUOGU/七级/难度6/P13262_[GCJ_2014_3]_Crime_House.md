# [GCJ 2014 #3] Crime House

## 题目描述

监控犯罪房屋的进出记录，有戴面具的人（id=0）。判断是否可能没有其他出入口，并求最少剩余人数。

## 输入格式

第一行 T。
每个用例第一行 N。
接下来 N 行，每行 E/L 和 id。

## 输出格式

输出 Case #x: y 或 CRIME TIME。

## 样例

### 样例 1
输入：
```
5
3
E 5
L 0
E 5
2
L 1
L 1
4
L 1
E 0
E 0
L 1
7
L 2
E 0
E 1
E 2
E 0
E 3
L 4
13
L 4
L 1
L 2
E 0
L 1
E 0
L 2
E 0
L 2
E 0
E 0
L 1
L 4
```
输出：
```
Case #1: 1
Case #2: CRIME TIME
Case #3: 1
Case #4: 4
Case #5: 0
```

## 提示

- 1 ≤ N ≤ 1000

## 解题思路

### 问题分析

需要模拟进出过程，判断是否可能。

### 核心思路

1. 贪心匹配面具人
2. 检查是否矛盾
3. 计算最少剩余人数

### 算法流程

1. 模拟进出过程
2. 贪心匹配
3. 输出结果

### 复杂度分析

- 时间复杂度：O(N^2)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        vector<char> type(N);
        vector<int> id(N);
        for (int i = 0; i < N; i++) cin >> type[i] >> id[i];
        
        vector<int> inside;
        int unknown_in = 0;
        bool impossible = false;
        
        for (int i = 0; i < N; i++) {
            if (type[i] == 'E') {
                if (id[i] == 0) unknown_in++;
                else inside.push_back(id[i]);
            } else {
                if (id[i] == 0) {
                    if (!inside.empty()) inside.pop_back();
                    else if (unknown_in > 0) unknown_in--;
                    else { impossible = true; break; }
                } else {
                    bool found = false;
                    for (int j = 0; j < inside.size(); j++) {
                        if (inside[j] == id[i]) {
                            inside.erase(inside.begin() + j);
                            found = true;
                            break;
                        }
                    }
                    if (!found) { impossible = true; break; }
                }
            }
        }
        
        if (impossible) cout << "Case #" << t << ": CRIME TIME" << endl;
        else cout << "Case #" << t << ": " << inside.size() + unknown_in << endl;
    }
    return 0;
}
```
