# P12990 [GCJ 2022 #1C] Letter Blocks

## 题目描述

You have built multiple separate towers of letter blocks. Now you want to combine all of them into a single megatower by stacking them. For any two blocks that have the same letter, all blocks between them must also have that letter. That is, each letter needs to appear in one contiguous group.

Given the towers you have built so far, can you stack them all up into a valid megatower?

## 输入格式

The first line gives the number of test cases $\mathbf{T}$. Each test case has two lines: an integer $\mathbf{N}$ and $\mathbf{N}$ strings $\mathbf{S}_1, \ldots, \mathbf{S}_N$.

## 输出格式

For each test case, output `Case #x: y` where $y$ is a valid megatower string, or `IMPOSSIBLE`.

## 样例

**输入样例 1**
```
6
5
CODE JAM MIC EEL ZZZZZ
6
CODE JAM MIC EEL ZZZZZ EEK
2
OY YO
2
HASH CODE
6
A AA BB A BA BB
2
CAT TAX
```
**输出样例 1**
```
Case #1: JAMMICCODEEELZZZZZ
Case #2: IMPOSSIBLE
Case #3: IMPOSSIBLE
Case #4: IMPOSSIBLE
Case #5: IMPOSSIBLE
Case #6: IMPOSSIBLE
```

## 解题思路

### 问题分析

每个字符串内部已经是合法的（字母连续）。拼接时，如果字母 $c$ 出现在多个字符串中，这些字符串必须排在一起（中间不能有不含 $c$ 的字符串），否则 $c$ 会被打断。

### 核心思路

1. **检查每个字符串内部是否合法**（字母是否连续）
2. **并查集合并**：对于每个字母，包含它的所有字符串必须在同一个块中
3. **块内拓扑排序**：块内字符串按尾首字母匹配关系排序
4. **块间拓扑排序**：块之间按尾首字母匹配关系排序
5. **最终验证**：拼接结果检查每个字母是否连续

### 关键点

- 并查集保证同一字母出现的字符串在同一块
- 块内和块间都需要拓扑排序来确定顺序
- 拓扑排序有环说明无解
- 拼接后需要最终验证（防止块内拓扑排序选出的排列不合法）

### 复杂度分析

- **时间复杂度**：$O(T \times N^2 \times L)$，其中 $L$ 是字符串平均长度
- **空间复杂度**：$O(N \times L)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int parent[105];
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void unite(int x, int y) { parent[find(x)] = find(y); }

bool is_valid(const string& s) {
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] != s[i-1]) {
            for (int k = i + 1; k < (int)s.size(); k++) {
                if (s[k] == s[i-1]) return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<string> s(n);
        for (int i = 0; i < n; i++) cin >> s[i];

        bool valid = true;
        for (int i = 0; i < n && valid; i++) {
            if (!is_valid(s[i])) valid = false;
        }
        if (!valid) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        for (int i = 0; i < n; i++) parent[i] = i;

        map<char, vector<int>> char_strings;
        for (int i = 0; i < n; i++) {
            for (char c : s[i]) {
                if (char_strings[c].empty() || char_strings[c].back() != i)
                    char_strings[c].push_back(i);
            }
        }
        for (auto& p : char_strings) {
            auto& vec = p.second;
            for (int k = 1; k < (int)vec.size(); k++)
                unite(vec[0], vec[k]);
        }

        map<int, vector<int>> block_members;
        for (int i = 0; i < n; i++)
            block_members[find(i)].push_back(i);

        vector<string> result_parts;
        for (auto& p : block_members) {
            auto& members = p.second;
            int sz = members.size();
            if (sz == 1) {
                result_parts.push_back(s[members[0]]);
                continue;
            }
            vector<vector<int>> adj(sz);
            vector<int> indeg(sz, 0);
            for (int i = 0; i < sz; i++)
                for (int j = 0; j < sz; j++)
                    if (i != j && s[members[i]].back() == s[members[j]].front()) {
                        adj[i].push_back(j);
                        indeg[j]++;
                    }
            vector<int> order, q;
            for (int i = 0; i < sz; i++)
                if (indeg[i] == 0) q.push_back(i);
            for (int qi = 0; qi < (int)q.size(); qi++) {
                int u = q[qi]; order.push_back(u);
                for (int v : adj[u])
                    if (--indeg[v] == 0) q.push_back(v);
            }
            if ((int)order.size() != sz) { valid = false; break; }
            string block_str;
            for (int idx : order) block_str += s[members[idx]];
            if (!is_valid(block_str)) { valid = false; break; }
            result_parts.push_back(block_str);
        }

        if (!valid) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        int nb = result_parts.size();
        vector<char> bf(nb), bl(nb);
        for (int i = 0; i < nb; i++) {
            bf[i] = result_parts[i].front();
            bl[i] = result_parts[i].back();
        }
        vector<vector<int>> badj(nb);
        vector<int> bindeg(nb, 0);
        for (int i = 0; i < nb; i++)
            for (int j = 0; j < nb; j++)
                if (i != j && bl[i] == bf[j]) { badj[i].push_back(j); bindeg[j]++; }
        vector<int> border, bq;
        for (int i = 0; i < nb; i++)
            if (bindeg[i] == 0) bq.push_back(i);
        for (int qi = 0; qi < (int)bq.size(); qi++) {
            int u = bq[qi]; border.push_back(u);
            for (int v : badj[u])
                if (--bindeg[v] == 0) bq.push_back(v);
        }
        if ((int)border.size() != nb) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }
        string result;
        for (int idx : border) result += result_parts[idx];
        if (!is_valid(result)) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }
        cout << "Case #" << t << ": " << result << "\n";
    }
    return 0;
}
```
