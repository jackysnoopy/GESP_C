# [KOI 2022 Round 1] ABBC

## 题目描述

试题来源：。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。

有一个只由 A、B、C 构成的字符串 $S$，长度为 $|S|$。你可以对这个字符串执行以下操作：

- 删除一个 A 及其后的某个 B；
- 删除一个 B 及其后的某个 C。

每个字符最多只能被删除一次。

例如，考虑字符串 ABCBA。将字符从左到右编号为 1、2、3……，可以如下操作：

- 删除第 1 个字符 A 和第 2 个字符 B。此时操作次数为 1，剩余字符串为 CBA。之后任意两字符都无法再满足操作条件，因此无法继续操作。
- 删除第 1 个字符 A 和第 4 个字符 B，然后删除第 2 个字符 B 和第 3 个字符 C。此时操作次数为 2，剩余字符串为 A。字符串中只剩一个字符，因此无法继续操作。

除此之外，还有其他可能的操作方案。

请你求出最多可以进行多少次这样的操作。

## 输入格式

第一行输入字符串 $S$。

## 输出格式

输出一行，表示最多可以进行的操作次数。

## 样例

### 样例输入 1
```
ABCBA
```

### 样例输出 1
```
2
```

### 样例输入 2
```
ABCBBACBABB
```

### 样例输出 2
```
5
```

## 提示

**约束条件**

- $1 \leq |S| \leq 300\,000$
- $S$ 中的所有字符均为 A、B 或 C

**子任务**

1. （5 分）$S$ 中的所有字符仅包含 A 和 B
2. （20 分）$|S| \leq 300$
3. （32 分）$|S| \leq 1\,000$
4. （43 分）无附加限制

翻译由 ChatGPT-4o 及人工完成

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int ans = 0;
    int a_count = 0, b_count = 0;

    for (char c : s) {
        if (c == 'A') a_count++;
        else if (c == 'B') {
            if (a_count > 0) {
                a_count--;
                ans++;
            } else {
                b_count++;
            }
        } else {
            if (b_count > 0) {
                b_count--;
                ans++;
            } else if (a_count > 0) {
                a_count--;
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
```

## 解题思路

### 问题分析

给定一个由 A、B、C 组成的字符串，每次操作可以删除一个 A 及其后的某个 B，或删除一个 B 及其后的某个 C。每个字符最多被删除一次。求最多可以进行多少次操作。

### 核心思路

贪心算法：从左到右扫描字符串，维护两个计数器 `a_count`（未匹配的 A 数量）和 `b_count`（未匹配的 B 数量）。遇到 B 时优先与之前的 A 配对（因为 A 只能与 B 配对），遇到 C 时优先与之前的 B 配对（因为 B 可以与 C 配对，而 A 只能与 B 配对，所以 B 留给 C 更优）。

### 算法流程

1. 初始化 ans = 0, a_count = 0, b_count = 0
2. 从左到右遍历字符串每个字符：
   - 若字符为 A：a_count++
   - 若字符为 B：
     - 若 a_count > 0：a_count--, ans++（与 A 配对删除）
     - 否则：b_count++（等待与后续 C 配对）
   - 若字符为 C：
     - 若 b_count > 0：b_count--, ans++（与 B 配对删除）
     - 否则若 a_count > 0：a_count--, ans++（与 A 配对删除，相当于 A-B-C 链中跳过 B 直接配对）
3. 输出 ans

### 复杂度分析

- 时间复杂度：O(n)，仅遍历字符串一次
- 空间复杂度：O(1)，仅使用常数个变量
