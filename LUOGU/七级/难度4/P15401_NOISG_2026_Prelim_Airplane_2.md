# [NOISG 2026 Prelim] Airplane 2

## 题目描述

After NOI 2023, Pan the Monkey has taken over control of an airplane from Benson the Rabbit. In the airplane, the passenger seats are arranged in $h$ rows and $w$ columns. The rows are numbered 1 to $h$ from top to bottom, and the columns are numbered 1 to $w$ from left to right. We refer to the seat located at row $i$ and column $j$ as $(i, j)$.

CEO Pan sells airplane tickets to $k$ passengers, who are numbered from 1 to $k$. The $i$-th passenger has a preferred column $c[i]$, but Pan may assign any row $r[i]$ for them to sit in. No two passengers may occupy the same seat.

To maintain an even weight distribution in the airplane, a passenger in an earlier row must not be seated in a later column. Formally, for any two assigned seats $(a_1, b_1)$ and $(a_2, b_2)$, if $a_1 < a_2$ then $b_1 \le b_2$.

CEO Pan defines the **Gross Passenger Satisfaction** as the **minimum** Manhattan distance between all pairs of assigned seats. The Manhattan distance between a pair of seats $(a_1, b_1)$ and $(a_2, b_2)$ is $|a_1 - a_2| + |b_1 - b_2|$, where $|x|$ is the absolute value of $x$.

Help Pan determine the **maximum** possible Gross Passenger Satisfaction over all valid assignments of rows, or determine that there is no valid assignment of rows.

## 输入格式

Your program must read from standard input.

The first line of input contains three space-separated integers $h$, $w$, and $k$.

The second line of input contains $k$ space-separated integers $c[1], c[2], \ldots, c[k]$.

## 输出格式

Your program must print to standard output.

Output one integer, the maximum Gross Passenger Satisfaction. If there is no valid assignment of rows, output $-1$.

## 样例

### 样例输入 1
```
5 1 6
1 1 1 1 1 1
```

### 样例输出 1
```
-1
```

### 样例输入 2
```
2 7 3
1 2 3
```

### 样例输出 2
```
1
```

### 样例输入 3
```
3 7 3
1 4 7
```

### 样例输出 3
```
4
```

### 样例输入 4
```
50 50 10
34 21 28 44 41 28 5 10 16 24
```

### 样例输出 4
```
9
```

### 样例输入 5
```
4 11 5
1 1 11 7 3
```

### 样例输出 5
```
2
```

## 提示

### Sample Test Case 1 Explanation

The airplane has $h = 5$ rows and $w = 1$ column. There are a total of $5 \times 1 = 5$ seats onboard. Therefore, it is impossible for Pan to assign unique seats for $k = 6$ passengers.

### Sample Test Case 5 Explanation

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/7glajhfc.png)
:::

One such valid assignment of rows that maximises the **Gross Passenger Satisfaction** is shown in the figure above. Each crossed grid indicates that the seat is assigned to a passenger. The first passenger is assigned to row 1, while the rest of the passengers are assigned to row 4.

The Manhattan distance between passengers 2 (seat $(4, 1)$) and 5 (seat $(4, 3)$) is $|4 - 4| + |1 - 3| = 2$ which is the minimum among all pairs of passengers. Hence, the **Gross Passenger Satisfaction** of this assignment is 2.

The figure below shows an example of an **invalid** assignment of rows. Although the **Gross Passenger Satisfaction** in this assignment is 3, passengers 3 (seat $(1, 11)$) and 4 (seat $(3, 7)$) would cause an uneven weight distribution since passenger 3 sits in an earlier row but in a later column than passenger 4.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/m6ge8jj8.png)
:::

### Subtasks

For all test cases, the input will satisfy the following bounds:

- $1 \le h, w \le 10^9$
- $2 \le k \le 200\,000$
- $1 \le c[i] \le w$ for all $1 \le i \le k$

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Score | Additional Constraints                      |
|:-------:|:-----:|:-------------------------------------------:|
| 0       | 0     | Sample test cases                           |
| 1       | 5     | $w = 1$                                     |
| 2       | 5     | $c[i] = i$ for all $1 \le i \le k$         |
| 3       | 7     | $c$ is an arithmetic sequence. $(c[i+1] - c[i] = c[i] - c[i-1])$ for all $2 \le i \le k-1$ |
| 4       | 9     | $h, w, k \le 8$                             |
| 5       | 31    | $h, w, k \le 3000$                          |
| 6       | 16    | $c[i] \ne c[j]$ for all $1 \le i < j \le k$ |
| 7       | 27    | No additional constraints                   |

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w, k;
    cin >> h >> w >> k;

    vector<int> c(k);
    for (int i = 0; i < k; i++) cin >> c[i];

    if (k > h * w) {
        cout << "-1\n";
        return 0;
    }

    sort(c.begin(), c.end());

    int ans = 0;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int dist = abs(c[i] - c[j]);
            ans = max(ans, dist);
        }
    }

    cout << ans << "\n";
    return 0;
}
```
