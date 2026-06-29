# P12938 [NERC 2019] Elections

## 题目描述

Byteburg Senate elections are coming. Usually "United Byteland", the ruling Byteland party, takes all the seats in the Senate. But this year there is one opposition candidate in one of the constituencies. You know the number of votes cast for each candidate at each polling station. The only thing you can do to prevent the election of the opposition candidate is to cancel the election results at some polling stations.

The opposition candidate will be elected if the sum of the votes cast in their favor at all non-canceled stations will be **strictly greater** than the analogous sum for every other candidate.

Your task is to prevent the election of the opposition candidate by canceling the election results at the minimal possible number of polling stations.

## 输入格式

The first line contains two integers $n$ and $m$ ($2 \leq n \leq 100$; $1 \leq m \leq 100$) — the number of candidates and the number of polling stations.

The next $m$ lines contain the election results at each polling station. In the $i$-th line the $j$-th number is $a_{i,j}$ — the number of votes cast for candidate $j$ at station $i$.

## 输出格式

In the first line output integer $k$ — the minimal number of polling stations to cancel. In the second line output $k$ integers — the indices of canceled polling stations, in any order.

## 样例

**输入样例 1**
```
5 3
6 3 4 2 8
3 7 5 6 7
5 2 4 7 9
```
**输出样例 1**
```
2
3 1
```

**输入样例 2**
```
2 1
1 1
```
**输出样例 2**
```
0
```

**输入样例 3**
```
3 3
2 3 8
4 2 9
3 1 7
```
**输出样例 3**
```
3
1 2 3
```

## 解题思路

### 问题分析

反对派（候选人 $n$）当选的条件是：在所有未取消的投票站中，反对派的总票数**严格大于**每个其他候选人的总票数。

要阻止反对派当选，只需要让反对派对**某个**候选人 $j$ 不再严格领先（即 $sum\_opp \leq sum\_j$）即可。

### 核心思路：搜索 + 启发式剪枝

由于 $n, m \leq 100$，可以用**迭代加深搜索**（IDA*）：

1. 定义 $total[j]$ = 反对派对候选人 $j$ 的总领先量（即 $\sum(a_{i,n} - a_{i,j})$）
2. 反对派不当选 $\Leftrightarrow$ 存在某个 $j$ 使得 $total[j] \leq 0$
3. 每次取消一个投票站，更新所有 $total[j]$
4. 迭代加深搜索：尝试取消 1 个、2 个、... 个投票站

### 启发式剪枝

对于每个候选人 $j$，计算需要取消多少个投票站才能使 $total[j] \leq 0$（按贡献从大到小贪心取消）。取所有 $j$ 中的**最小值**作为下界——因为我们只需要让一个 $j$ 的约束满足即可。

### 复杂度分析

- **时间复杂度**：最坏 $O(C(m, k))$，其中 $k$ 是答案。启发式剪枝大幅减少搜索空间。
- **空间复杂度**：$O(n \times m)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int a[105][105];
int total[105];
int ans;
int cur_stations[105];
int cur_cnt;

// 反对派不当选：存在某个j使得total[j] <= 0
bool check() {
    for (int j = 1; j < n; j++) {
        if (total[j] <= 0) return true;
    }
    return false;
}

// 启发式下界：让某个j的total[j]<=0至少需要取消多少个投票站
int heuristic() {
    int h = m + 1;
    for (int j = 1; j < n; j++) {
        if (total[j] <= 0) return 0;
        vector<int> contribs;
        for (int i = 0; i < m; i++) {
            int b = a[i][n] - a[i][j];
            if (b > 0) contribs.push_back(b);
        }
        sort(contribs.begin(), contribs.end(), greater<int>());
        int need = total[j];
        int cnt = 0;
        for (int c : contribs) {
            need -= c;
            cnt++;
            if (need <= 0) break;
        }
        h = min(h, cnt);
    }
    return h;
}

bool dfs(int idx, int depth, int max_depth) {
    if (check()) return true;
    if (depth >= max_depth) return false;
    if (depth + heuristic() > max_depth) return false;

    for (int i = idx; i < m; i++) {
        cur_stations[cur_cnt++] = i + 1;
        for (int j = 1; j < n; j++) {
            total[j] -= (a[i][n] - a[i][j]);
        }
        if (dfs(i + 1, depth + 1, max_depth)) return true;
        for (int j = 1; j < n; j++) {
            total[j] += (a[i][n] - a[i][j]);
        }
        cur_cnt--;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for (int j = 1; j < n; j++) {
        total[j] = 0;
        for (int i = 0; i < m; i++) {
            total[j] += a[i][n] - a[i][j];
        }
    }

    if (check()) {
        cout << "0\n";
        return 0;
    }

    for (ans = 1; ans <= m; ans++) {
        cur_cnt = 0;
        if (dfs(0, 0, ans)) {
            cout << ans << "\n";
            for (int i = 0; i < ans; i++) {
                if (i > 0) cout << " ";
                cout << cur_stations[i];
            }
            cout << "\n";
            return 0;
        }
    }

    return 0;
}
```
