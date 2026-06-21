# [COI 2011] 河流 / RIJEKA

## 题目描述

译自 [COI 2011 T3](https://hsin.hr/hio2011/zadaci/)。

在一个遥远的国度，有一条大河，沿岸分布着许多村庄。村庄按河流沿岸的顺序从 $0$ 到 $M$ 编号。相邻两个村庄之间的距离恰好为 $1$ 公里。

在编号为 $0$ 的村庄里，住着一位名叫 Mirko 的村民，他拥有一艘船，专门从事村庄间的客运服务。今天， Mirko 需要从 $0$ 号村庄出发前往 $M$ 号村庄，并在途中运送一些乘客。具体来说，今天共有 $N$ 名乘客需要出行，每名乘客的当前所在村庄和目的村庄均已知晓。

Mirko 的船容量很大，可以同时搭载任意数量的乘客。
例如，乘客 A 需要从 $2$ 号村庄前往 $8$ 号村庄，乘客 B 需要从 $6$ 号村庄前往 $4$ 号村庄。那么 Mirko 从 $0$ 号村庄出发后可以这样操作：在 $2$ 号村庄接上乘客 A，继续行驶至 $6$ 号村庄接上乘客 B，然后返回 $4$ 号村庄让乘客 B 下船，再继续行驶至 $8$ 号村庄让乘客 A 下船，最后前往 M 号村庄。此方案对应下文第一个测试样例。

请编写程序计算 Mirko 从 $0$ 号村庄出发，将所有乘客运送至目的地，并最终成功到达 $M$ 号村庄所需行驶的最小总公里数。

## 输入格式

第一行输入两个自然数 $N$ 和 $M$ $(N \le 300,000, 3 \le M \le 10^9)$，含义如题目描述，以空格分隔。

接下来 $N$ 行每行包含两名乘客的信息，一行输入两个不同的整数（均大于 $0$ 且小于 $M$ ），分别表示该乘客的出发村庄和目的村庄。

## 输出格式

输出一行一个整数，表示 Mirko 行驶路径的最小总公里数。

## 样例

### 样例输入 1
```
2 10 
2 8 
6 4
```

### 样例输出 1
```
14
```

### 样例输入 2
```
8 15 
1 12 
3 1 
3 9 
4 2 
7 13 
12 11 
14 11 
14 13
```

### 样例输出 2
```
27
```

## 提示

对于 $40\%$ 的测试数据满足：$N \le 5000$。

对于另外 $50\%$ 的测试数据满足：$M \le 2,000,000$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> passengers(N);
    for (int i = 0; i < N; i++) {
        cin >> passengers[i].first >> passengers[i].second;
    }

    sort(passengers.begin(), passengers.end());

    long long total = M;
    int cur = 0;

    for (auto& [from, to] : passengers) {
        if (from > cur) {
            total += from - cur;
            cur = from;
        }
        if (to > cur) {
            cur = to;
        } else {
            total += cur - to;
            cur = to;
        }
    }

    total += M - cur;

    cout << total << "\n";
    return 0;
}
```
