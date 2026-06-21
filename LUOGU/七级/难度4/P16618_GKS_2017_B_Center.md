# [GKS 2017 #B] Center

## 题目描述

There are $N$ weighted points in a plane. Point $i$ is at ($X_i$, $Y_i$) and has weight $W_i$.

In this problem, we need to find a special center of these points. The center is a point ($X$, $Y$) such that the sum of $\max(|X-X_i|, |Y-Y_i|) \times W_i$ is minimum.

## 输入格式

The input starts with one line containing exactly one integer $T$, which is the number of test cases. $T$ test cases follow.

Each test case begins with one line containing one integer $N$. $N$ lines follow. Each line contains three space-separated real numbers $X_i$, $Y_i$, and $W_i$. $X_i$, $Y_i$ and $W_i$ have exactly 2 digits after the decimal point.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the sum of $\max(|X-X_i|, |Y-Y_i|) \times W_i$ for center ($X$, $Y$).

$y$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.

## 样例

### 样例输入 1
```
3
2
0.00 0.00 1.00
1.00 0.00 1.00 
4
1.00 1.00 1.00
1.00 -1.00 1.00
-1.00 1.00 1.00
-1.00 -1.00 1.00 
2
0.00 0.00 1.00
1.00 0.00 2.00
```

### 样例输出 1
```
Case #1: 1.0
Case #2: 4.0
Case #3: 1.0
```

## 提示

**Limits**

$1 \le T \le 10$.

$-1000.00 \le X_i \le 1000.00$.

$-1000.00 \le Y_i \le 1000.00$.

**Small dataset (Test set 1 - Visible)**

$1 \le N \le 100$;

$W_i = 1.0$, for all i.

**Large dataset (Test set 2 - Hidden)**

$1 \le N \le 10000$;

$1.0 \le W_i \le 1000.0$, for all i.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;

        vector<double> x(n), y(n), w(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> w[i];

        double best_x = 0, best_y = 0;
        double best_cost = 1e18;

        for (int iter = 0; iter < 100; iter++) {
            double cx = best_x, cy = best_y;
            double total_w = 0;
            for (int i = 0; i < n; i++) {
                double dx = abs(cx - x[i]);
                double dy = abs(cy - y[i]);
                if (dx > dy) {
                    total_w += w[i];
                } else {
                    total_w += w[i];
                }
            }

            double new_x = 0, new_y = 0, new_w = 0;
            for (int i = 0; i < n; i++) {
                double dx = abs(cx - x[i]);
                double dy = abs(cy - y[i]);
                if (dx >= dy) {
                    new_x += w[i] * x[i];
                    new_y += w[i] * y[i];
                    new_w += w[i];
                }
            }

            if (new_w > 0) {
                best_x = new_x / new_w;
                best_y = new_y / new_w;
            }
        }

        double ans = 0;
        for (int i = 0; i < n; i++) {
            ans += w[i] * max(abs(best_x - x[i]), abs(best_y - y[i]));
        }

        cout << "Case #" << t << ": " << fixed << setprecision(1) << ans << "\n";
    }

    return 0;
}
```
