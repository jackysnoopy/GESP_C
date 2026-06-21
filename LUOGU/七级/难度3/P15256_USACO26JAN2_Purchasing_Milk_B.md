# [USACO26JAN2] Purchasing Milk B

## 题目描述

On National Milk Day, Farmer John is offering exclusive prices on buckets of milk! He has $N$ ($1 \leq N \leq 10^5$) deals numbered from $1$ to $N$. For the $i$'th deal, he is offering $2^{i-1}$ buckets of milk for $a_i$ ($1 \leq a_i \leq 10^9, a_i < a_{i+1}$) moonies. The same deal may be taken any non-negative integer number of times.

You are thinking about $Q$ ($1 \leq Q \leq 10^4$) independent queries. For each query, you have an integer $x$ ($1 \leq x \leq 10^9$) in mind and wonder what is the minimum cost to purchase at least $x$ buckets of milk.

## 输入格式

The first line contains two integers $N$ and $Q$.

The following line contains $a_1, a_2, \ldots, a_N$.

Each of the following $Q$ lines contains an integer $x$, representing a query.

## 输出格式

For each query, output the minimum cost on a new line.

Note that the large size of integers involved in this problem may require the use of 64-bit integer data types (e.g., a "long long" in C/C++).

## 样例

### 样例输入 1
```
2 4
10 15
1
2
6
7
```

### 样例输出 1
```
10
15
45
55
```

### 样例输入 2
```
4 10
10 25 30 70
1
2
3
4
5
6
7
8
15
101
```

### 样例输出 2
```
10
20
30
30
40
50
60
60
120
760
```

## 提示

### Sample 1 Explanation

In the example above, Farmer John is offering 2 deals: 1 bucket of milk for 10 moonies and 2 buckets of milk for 15 moonies.
The cheapest cost to buy 1 bucket is just the cost of the 1 bucket deal and the cheapest cost to buy 2 buckets is just the cost of the 2 bucket deal.

To get 6 buckets, the cheapest way is to purchase 3 of the 2 bucket deal for a total of 45 moonies.

To get 7 buckets, the cheapest way is to purchase 3 of the 2 bucket deal and 1 of the 1 bucket deal for a total of 55 moonies.

### Sample 2 Explanation

In this example, Farmer John is offering a total of 4 deals for 1, 2, 4, and 8 buckets. For each of the 10 queries, the corresponding output indicates the minimum cost to purchase at least that amount of milk. Sometimes, it is cheaper to purchase more than the specified amount.

SCORING:
- Inputs 3-4: $N \leq 2$
- Inputs 5-8: $N \leq 10$
- Inputs 9-16: No additional constraints.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b;
    cin >> n >> b;

    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    sort(prices.begin(), prices.end());

    int cnt = 0;
    for (int p : prices) {
        if (b >= p) {
            b -= p;
            cnt++;
        }
    }

    cout << cnt << "\n";
    return 0;
}
```
