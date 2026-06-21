# WIDGET - Widget Factory

## 题目描述

一个零件工厂生产$N$种零件，第$i$种零件的生产天数在$ 3$天到$9$天之间，且一定是一个整数。

有$M$条记录，每一条记录记录着某个工人的工作情况：开始工作在星期几、结束工作在星期几、在这段时间内共做了哪些零件。

假设工人在工作期间没有放假，开始工作当天和结束工作当天在工作，且零件刚好做完，试通过这$M$条记录得到每一种零件的生产天数。

### 输入数据

有若干组输入数据。

每一组输入的第一行两个正整数$N\ M(1 \leq N,M \leq 300)$表示加工的数量和记录的数量。

接下来$2M$行每两行描述一条记录。

每一条记录的第一行一个正整数$k(1 \leq k \leq 10000)$和两个字符串$S\ T$，$S\ T$分别表示开始工作在星期几和结束工作在星期几，只有`SUN MON TUE WED THU FRI SAT`$7$种可能，$k$表示这段时间内工人加工的零件数量；

第二行$k$个正整数$a_i$表示加工的零件的种类，可能存在某些$a_i$相等。

## 输入格式

```
4 TUE SUN
13 18 1 13
```

当$N=M=0$时表示输入结束

## 输出格式

对于每一组数据输出一行。如果存在唯一解输出$N$个正整数，第$i$个正整数表示第$i$个零件的加工时间，**注意输出时第一个数之前和最后一个数之后不能有空格，而两个数之间严格有一个空格**；如果存在多解输出`Multiple solutions.`；如果无解输出`Inconsistent data.`。

## 样例

### 样例输入
```
2 3
2 MON THU
1 2
3 MON FRI
1 1 2
3 MON SUN
1 2 2
10 2
1 MON TUE 
3
1 MON WED
3
0 0
```

### 样例输出
```
8 3
Inconsistent data.
```

## 提示



## 解题思路

### 问题分析

Widget Factory，根据工人工作记录推断每种零件的生产天数。

### 核心思路

1. 每个零件生产天数 3-9 天，减 2 后为 1-7。
2. 每条记录给出开始/结束星期和零件编号，可列方程。
3. 用高斯消元求解模 7 的线性方程组。

### 算法流程

1. 读入多组数据
2. 对每组构造方程组
3. 高斯消元 mod 7
4. 输出结果或 Inconsistent

### 复杂度分析

时间 O(M * N^2)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int day(string s) {
    map<string,int> mp = {{"MON",0},{"TUE",1},{"WED",2},{"THU",3},{"FRI",4},{"SAT",5},{"SUN",6}};
    return mp[s];
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<vector<int>> a(m, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            int cnt; string d1, d2;
            cin >> cnt >> d1 >> d2;
            a[i][n] = (day(d2) - day(d1) + 1) % 7;
            for (int j = 0; j < cnt; ++j) { int x; cin >> x; a[i][x - 1]++; }
        }
        int rank = 0;
        for (int col = 0; col < n && rank < m; ++col) {
            int mx = rank;
            for (int r = rank + 1; r < m; ++r)
                if (a[r][col]) { mx = r; break; }
            if (!a[mx][col]) continue;
            swap(a[rank], a[mx]);
            long long inv = 1;
            for (int p = 5; p >= 0; --p) inv = inv * inv % 7;
            for (int r = 0; r < m; ++r) {
                if (r == rank || !a[r][col]) continue;
                int f = a[r][col] * inv % 7;
                for (int c = col; c <= n; ++c)
                    a[r][c] = (a[r][c] - f * a[rank][c] % 7 + 14) % 7;
            }
            rank++;
        }
        bool bad = false;
        for (int r = rank; r < m; ++r) if (a[r][n]) { bad = true; break; }
        if (bad) { cout << "Inconsistent data." << '\n'; continue; }
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            int val = 0;
            for (int r = 0; r < rank; ++r) if (a[r][i]) { val = a[r][n]; break; }
            cout << (val % 7 + 2) % 7 + (val % 7 == 0 ? 7 : 0);
        }
        cout << '\n';
    }
    return 0;
}
```
