# [GKS 2018 #A] Even Digits

## 题目描述

Supervin has a unique calculator. This calculator only has a display, a plus button, and a minus button. Currently, the integer $N$ is displayed on the calculator display.

Pressing the plus button increases the current number displayed on the calculator display by $1$. Similarly, pressing the minus button decreases the current number displayed on the calculator display by $1$. The calculator does not display any leading zeros. For example, if $100$ is displayed on the calculator display, pressing the minus button once will cause the calculator to display $99$.

Supervin does not like odd digits, because he thinks they are "odd". Therefore, he wants to display an integer with only even digits in its decimal representation, using only the calculator buttons. Since the calculator is a bit old and the buttons are hard to press, he wants to use a minimal number of button presses.

Please help Supervin to determine the minimum number of button presses to make the calculator display an integer with no odd digits.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line containing an integer $N$: the integer initially displayed on Supervin's calculator.

## 输出格式

For each test case, output one line containing Case #x: y, where $x$ is the test case number (starting from $1$) and $y$ is the minimum number of button presses, as described above.

## 样例

### 样例输入 1
```
4
42
11
1
2018
```

### 样例输出 1
```
Case #1: 0
Case #2: 3
Case #3: 1
Case #4: 2
```

## 提示

In Sample Case #1, the integer initially displayed on the calculator has no odd digits, so no button presses are needed.

In Sample Case #2, pressing the minus button three times will cause the calculator to display $8$. There is no way to satisfy the requirements with fewer than three button presses.

In Sample Case #3, either pressing the minus button once (causing the calculator to display $0$) or pressing the plus button once will cause the calculator to display an integer without an odd digit.

In Sample Case #4, pressing the plus button twice will cause the calculator to display $2020$. There is no way to satisfy the requirements with fewer than two button presses.

### Limits

$1 \le T \le 100$.

**Small dataset (Test set 1 - Visible)**

$1 \le N \le 10^5$.

**Large dataset (Test set 2 - Hidden)**

$1 \le N \le 10^{16}$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int evenCount = 0;
    for (char c : s) {
        if ((c - '0') % 2 == 0) evenCount++;
    }

    cout << evenCount << "\n";
    return 0;
}
```
