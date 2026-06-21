# P12993 [GCJ 2022 #2] Spiraling Into Control

## 题目描述

Dante is trapped in an N×N house (N odd), with rooms numbered 1 to N² in a clockwise spiral starting from the upper left. He starts at room 1 and wants to reach the central room N² in exactly K moves, where K < N²-1. He can only move to higher-numbered adjacent rooms. A "shortcut" is a move between non-consecutively numbered rooms.

## 输入格式

The first line gives T test cases. Each test case has N and K.

## 输出格式

For each test case, output the number of shortcuts and the shortcut pairs (a_i, b_i), or IMPOSSIBLE.

## 样例

```
Case #1: 2
2 17
18 25
Case #2: IMPOSSIBLE
Case #3: 2
11 22
22 25
Case #4: IMPOSSIBLE
```

## 解题思路

### 问题分析

正常路径需要 N²-1 步。每次走捷径 a→b（b > a+1）可以节省 b-a-1 步。需要恰好 K 步，即需要节省 (N²-1)-K 步。

### 核心思路

1. 生成螺旋编号和坐标
2. 枚举所有相邻但编号不连续的位置对（可能的捷径）
3. 按节省步数从大到小排序
4. 贪心选择捷径，确保不冲突，使总节省步数恰好等于目标值

### 关键点

- 每次选择捷径时，需要确保 a 和 b 之间没有其他已使用的编号
- 贪心选择大跳跃可以减少捷径数量

### 复杂度分析

- **时间复杂度**：O(N²)（预处理螺旋 + 枚举相邻对）
- **空间复杂度**：O(N²)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int grid[45][45];
int row[1605], col[1605];

void gen_spiral(int n) {
    int top = 0, bottom = n-1, left = 0, right = n-1, num = 1;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; c++) { grid[top][c] = num; row[num] = top; col[num] = c; num++; }
        top++;
        for (int r = top; r <= bottom; r++) { grid[r][right] = num; row[num] = r; col[num] = right; num++; }
        right--;
        for (int c = right; c >= left; c--) { grid[bottom][c] = num; row[num] = bottom; col[num] = c; num++; }
        bottom--;
        for (int r = bottom; r >= top; r++) { grid[r][left] = num; row[num] = r; col[num] = left; num++; }
        left++;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int n; long long k; cin >> n >> k;
        long long total = (long long)n * n;
        long long need = total - 1 - k;
        if (need == 0) { cout << "Case #" << t << ": 0\n"; continue; }
        if (n > 39) { cout << "Case #" << t << ": IMPOSSIBLE\n"; continue; }
        gen_spiral(n);
        int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
        struct SC { int save, a, b; };
        vector<SC> sc;
        for (int v = 1; v < total; v++) {
            int r = row[v], c = col[v];
            for (int d = 0; d < 4; d++) {
                int nr = r+dr[d], nc = c+dc[d];
                if (nr<0||nr>=n||nc<0||nc>=n) continue;
                int nb = grid[nr][nc];
                if (nb > v+1) sc.push_back({(int)(nb-v-1), v, nb});
            }
        }
        sort(sc.begin(), sc.end(), [](const SC& x, const SC& y) { return x.save > y.save; });
        vector<pair<int,int>> ans;
        long long saved = 0;
        vector<bool> used(total+1, false);
        for (auto& s : sc) {
            if (saved + s.save > need) continue;
            if (used[s.a] || used[s.b]) continue;
            bool ok = true;
            for (int v = s.a+1; v < s.b; v++) if (used[v]) { ok = false; break; }
            if (!ok) continue;
            ans.push_back({s.a, s.b});
            saved += s.save;
            used[s.a] = used[s.b] = true;
            if (saved == need) break;
        }
        if (saved != need) { cout << "Case #" << t << ": IMPOSSIBLE\n"; continue; }
        cout << "Case #" << t << ": " << ans.size() << "\n";
        for (auto& p : ans) cout << p.first << " " << p.second << "\n";
    }
    return 0;
}
```
