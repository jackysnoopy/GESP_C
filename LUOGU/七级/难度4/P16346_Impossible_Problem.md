# Impossible Problem

## 题目描述

本题出处：https://www.luogu.com.cn/contest/314899

有一个长度为 $n$ 的序列 $a$，每次可以选择一个区间满足这个区间的数字和为奇数，然后将这个区间中的所有数加上 $1$。

求是否可以将序列中的所有数字变为相同数字。

若可以则输出 `Yes`，否则输出 `No`。

## 输入格式

本题多测，第一行输入一行一个正整数 $T$。

对于每组测试数据：

- 第一行输入一行一个正整数 $n$。
- 第二行输入一行 $n$ 个非负整数表示序列 $a$。

## 输出格式

对于每组测试数据：

- 一行一个字符串表示你的答案。

## 样例

### 样例输入 1
```
2
2
1 2
2
2 4
```

### 样例输出 1
```
Yes
No
```

## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1 \le T \le 10^4$，$1 \le n \le 500$，$1 \le a_i \le 10^{9}$。

| 测试点编号 | $n \le$ | 分值 |
|:-:|:-:|:-:|
| $1$ | $1$ | $10$ |
| $2$ | $2$ | $10$ |
| $3$ | $3$ | $10$ |
| $4$ | $4$ | $10$ |
| $5$ | $5$ | $10$ |
| $6$ | $6$ | $10$ |
| $7$ | $7$ | $10$ |
| $8$  | $8$ | $10$ |
| $9$ | $9$ | $10$ |
| $10$ | $500$ | $10$ |

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long sum = 0;
        for (int i = 0; i < n; i++) sum += a[i];

        if (sum % n != 0) {
            cout << "No\n";
            continue;
        }

        long long target = sum / n;
        long long diff = 0;
        bool possible = true;

        for (int i = 0; i < n; i++) {
            diff += a[i] - target;
            if (diff < 0) {
                possible = false;
                break;
            }
        }

        cout << (possible ? "Yes" : "No") << "\n";
    }

    return 0;
}
```
