# [NERC 2019] Elections

## 题目描述

Byteburg Senate elections are coming. Usually "United Byteland", the ruling Byteland party, takes all the seats in the Senate to ensure stability and sustainable development. But this year there is one opposition candidate in one of the constituencies. Even one opposition member can disturb the stability in the Senate, so the head of the Party asks you to ensure that the opposition candidate will not be elected.

There are $n$ candidates, numbered from 1 to $n$. Candidate $n$ is the opposition candidate. There are $m$ polling stations in the constituency, numbered from 1 to $m$. You know the number of votes cast for each candidate at each polling station. The only thing you can do to prevent the election of the opposition candidate is to cancel the election results at some polling stations. The opposition candidate will be elected if the sum of the votes cast in their favor at all non-canceled stations will be **strictly greater** than the analogous sum for every other candidate. 

Your task is to prevent the election of the opposition candidate by canceling the election results at the minimal possible number of polling stations. Notice that solution always exists, because if you cancel the elections at all polling stations, the number of votes for each candidate will be 0, and the opposition candidate will not be elected.

## 输入格式

The first line of the input contains two integers $n$ and $m$ ($2\le n\le 100$; $1\le m \le 100$) --- the number of candidates and the number of polling stations. The next $m$ lines contain the election results at each polling station with $n$ numbers on each line. In the $i$-th line the $j$-th number is $a_{i,j}$ --- the number of votes cast for the candidate $j$ at the station $i$ ($0\le a_{i,j} \le 1\,000$).

## 输出格式

In the first line output integer $k$ --- the minimal number of the polling stations in which you need to cancel the election results. In the second line output $k$ integers --- the indices of canceled polling stations, in any order. If there are multiple ways to cancel results at $k$ stations, output any one of them.

## 样例

### 样例输入 1
```
5 3
6 3 4 2 8
3 7 5 6 7
5 2 4 7 9
```

### 样例输出 1
```
2
3 1
```

### 样例输入 2
```
2 1
1 1
```

### 样例输出 2
```
0
```

### 样例输入 3
```
3 3
2 3 8
4 2 9
3 1 7
```

### 样例输出 3
```
3
1 2 3
```

## 提示

In the first example, the candidates from 1 to 5 received 14, 12, 13, 15, and 24 votes correspondingly. The opposition candidate has the most votes. However, if you cancel the election results at the first and the third polling stations, then only the result from the second polling station remains and the vote sums become 3, 7, 5, 6, and 7, without the opposition candidate being in the lead anymore.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> votes(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> votes[i][j];
        }
    }

    vector<int> total(n, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            total[j] += votes[i][j];
        }
    }

    int opp = total[n - 1];
    int max_other = *max_element(total.begin(), total.end() - 1);

    if (opp <= max_other) {
        cout << "0\n";
        return 0;
    }

    vector<int> order(m);
    for (int i = 0; i < m; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return votes[x][n - 1] > votes[y][n - 1];
    });

    vector<int> canceled;
    for (int i : order) {
        canceled.push_back(i + 1);
        total[n - 1] -= votes[i][n - 1];
        for (int j = 0; j < n - 1; j++) {
            total[j] -= votes[i][j];
        }
        opp = total[n - 1];
        max_other = *max_element(total.begin(), total.end() - 1);
        if (opp <= max_other) break;
    }

    cout << canceled.size() << "\n";
    for (int i = 0; i < (int)canceled.size(); i++) {
        if (i) cout << " ";
        cout << canceled[i];
    }
    cout << "\n";

    return 0;
}
```

## 解题思路

### 问题分析
给定 n 个候选人和 m 个投票站的投票结果，候选人 n 是反对党候选人。需要取消最少数量投票站，使得反对党候选人不再是得票数严格大于所有其他候选人的那个。要求输出取消的投票站数量和编号。

### 核心思路
贪心策略：按反对党候选人在各投票站的得票数从大到小排序，依次取消，直到反对党不再领先。这是因为取消反对党得票最多的投票站能最有效地降低其总票数。

### 算法流程
1. 读入所有投票站的投票数据
2. 计算每个候选人的总票数
3. 若反对党总票数已经 ≤ 其他候选人的最大总票数，直接输出 0
4. 否则，按反对党在各站的得票数降序排序投票站
5. 依次取消投票站，每取消一个就更新总票数
6. 每次更新后检查反对党是否仍领先，一旦不再领先就停止
7. 输出取消的投票站数量和编号

### 复杂度分析
- 时间复杂度：O(m·n + m·log(m))，其中排序 O(m·log(m))，每次更新 O(n)，最多 m 次更新
- 空间复杂度：O(m·n)，存储投票数据
