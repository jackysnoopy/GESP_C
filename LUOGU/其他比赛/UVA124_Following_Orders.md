# UVA124 - Following Orders (跟随顺序)

## 题目描述

给定一组变量和若干约束条件 `x < y`（表示 x 必须排在 y 前面），生成所有满足约束条件的拓扑排序序列。

## 输入格式

- 第一行：变量集（以字符串形式给出，如 `a b c`）
- 后续行：约束对，每对两个变量，表示前一个必须排在后一个前面
- 输入以 `#` 结束

## 输出格式

- 每行输出一个合法的拓扑排序序列
- 按字典序排序
- 多组测试数据之间输出一个空行

## 样例

### 输入
```
a b c
a b c b a
#
```

### 输出
```
a b c
a c b
b a c

```

## 解题思路

### 问题分析

本题要求枚举所有满足偏序关系的全排列，即所有合法的拓扑排序。变量数量最多为 20 个，但由于需要输出所有方案，实际搜索空间较大。

### 核心思路

1. **建图**：根据约束 `x < y` 建立有向图，`x` 到 `y` 有一条有向边
2. **拓扑排序枚举**：使用 DFS 递归枚举所有拓扑排序
3. **字母序保证**：对变量排序后按序枚举，自然保证输出字典序

### 算法流程

1. 读入变量集，建立字符到索引的映射
2. 读入约束，建立邻接矩阵，记录入度
3. DFS 枚举：每一步选择一个入度为 0 且未使用的变量，加入当前序列，更新入度
4. 当序列长度等于变量数时，输出一个完整排列

### 复杂度分析

- 时间复杂度：O(n!)，最坏情况下需要枚举所有排列
- 空间复杂度：O(n²)，用于存储图结构

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int n;
vector<char> vars;
bool adj[26][26];
bool used[26];
char order[26];

void dfs(int depth, vector<int>& inDeg) {
    if (depth == n) {
        for (int i = 0; i < n; i++) cout << order[i] << (i < n - 1 ? " " : "\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        int idx = vars[i] - 'a';
        if (!used[idx] && inDeg[idx] == 0) {
            used[idx] = true;
            order[depth] = vars[i];
            vector<int> newDeg(inDeg);
            for (int j = 0; j < 26; j++) {
                if (adj[idx][j]) newDeg[j]--;
            }
            dfs(depth + 1, newDeg);
            used[idx] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    bool first = true;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line == "#") break;

        vars.clear();
        memset(adj, 0, sizeof(adj));
        memset(used, 0, sizeof(used));

        for (char c : line) {
            if (c != ' ') vars.push_back(c);
        }
        sort(vars.begin(), vars.end());
        n = vars.size();

        vector<int> inDeg(26, 0);
        string constraintLine;
        while (getline(cin, constraintLine)) {
            if (constraintLine == "#" || constraintLine.empty()) {
                if (constraintLine == "#") break;
                continue;
            }
            char x = constraintLine[0], y = constraintLine[2];
            if (!adj[x - 'a'][y - 'a']) {
                adj[x - 'a'][y - 'a'] = true;
                inDeg[y - 'a']++;
            }
        }

        if (!first) cout << "\n";
        first = false;
        dfs(0, inDeg);
    }

    return 0;
}
```
