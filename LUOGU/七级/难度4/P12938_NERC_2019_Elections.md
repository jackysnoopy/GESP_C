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
