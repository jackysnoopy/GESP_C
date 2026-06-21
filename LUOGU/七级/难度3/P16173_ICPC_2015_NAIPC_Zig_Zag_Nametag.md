# [ICPC 2015 NAIPC] Zig Zag Nametag

## 题目描述

When ninjas go to conferences they wear fake nametags. One ninja in particular wants to impress his Sensei. His Sensei chooses a new favorite number every day. The pupil wants to put a name on his nametag that encodes his Sensei’s favorite number! This name will consist of only lower case letters. He assigns a value to each letter, based on its position in the alphabet (e.g. a = 1, b = 2, ..., z = 26). Then, he encodes the Sensei’s number by adding up the absolute values of the differences of every consecutive pair of letters. For example, the string a z x b has the value of:

$$
|a - z| + |z - x| + |x - b| = |1 - 26| + |26 - 24| + |24 - 2| = 49
$$

The name that the ninja will write on his nametag is the shortest string that encodes to his Sensei’s favorite number. If there’s more than one string of the shortest length, he’ll choose the one that comes first alphabetically. Given the Sensei’s favorite number, $k$, find the string that the ninja should put on his nametag.

## 输入格式

Each input will consist of a single test case. Note that your program may be run multiple times on different inputs. Each input consists of a single line with a single integer $k$ ($1 \leq k \leq 1\,000\,000$), which is the Sensei’s favorite number. There will always be a name that encodes to the Sensei’s number.

## 输出格式

Output a single line with a string of lower case letters, which is the name that the ninja should put on the nametag to impress the Sensei.

## 样例

### 样例输入 1
```
1
```

### 样例输出 1
```
ab
```

### 样例输入 2
```
19
```

### 样例输出 2
```
at
```

### 样例输入 3
```
77
```

### 样例输出 3
```
aoazb
```

## 提示

难度：普及/提高−

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) ans -= n - i + 1;
        else ans += n - i + 1;
    }

    cout << abs(ans) << "\n";
    return 0;
}
```
