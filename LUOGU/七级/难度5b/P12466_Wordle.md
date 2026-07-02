# 『FCRT / 1 - 3』Wordle

## 题目描述

**这是一道交互题。**

凯撒加密算法的流程如下：

- 对于仅由**英文大小写字母**构成的字符串 $S$，指定确定的加密参数 $k$，再将 $S$ 中的每个字母替换为字母表中**循环右移** $k$ 位的字母，最终得到加密后的字符串。
- 字母表顺序为 $\texttt{A} \sim \texttt{Z}$ 后接 $\texttt{a} \sim \texttt{z}$，因此 $\texttt{z}$ 右移一位为 $\texttt{A}$，$\texttt{Z}$ 右移一位为 $\texttt{a}$。

例如，当 $S=\texttt{abyz}$，$k=2$ 时，可以得到加密结果为 $\texttt{cdAB}$。

现在有 $q$ 个经过凯撒加密的字符串 $T$。对于每组测试，你需要通过若干次询问解密出原文 $S$。

每次询问，你可以猜测一个字符串 $S'$，交互库会返回 $S'$ 与原文 $S$ 中字符相同的位置数。你需要保证 $\lvert S'\rvert=\lvert S\rvert$。如果猜测完全正确（返回值为 $\lvert T\rvert$），则当前测试结束，进入下一组测试。

每组测试最多询问 $52$ 次。

## 输入格式

第一行，一个整数 $q$ 表示数据组数。

对于每组数据，交互库会先输出一行一个字符串 $T$，表示加密结果。

每次询问时，输出一行一个长度为 $\lvert T\rvert$ 的字符串 $S'$，表示你的猜测。交互库会返回一个整数 $x$，表示 $S'$ 与原文 $S$ 中字符相同的位置数。

## 输出格式

每次询问输出一行猜测字符串。若猜测正确则进入下一组测试。

## 样例

**样例 1：**

交互过程（仅供参考）：

1. 原文为 $\texttt{abyz}$，加密密钥 $k=2$，密文为 $\texttt{cdAB}$。
2. 原文为 $\texttt{century}$，加密密钥 $k=1$，密文为 $\texttt{dfouvsz}$。

## 提示

**【数据范围】**

- Subtask 1（4 Points）：$\lvert T\rvert = 1$。
- Subtask 2（10 Points）：$2 \le \lvert T\rvert \le 4$。
- Subtask 3（9 Points）：$5 \le \lvert T\rvert \le 8$。
- Subtask 4（9 Points）：$9 \le \lvert T\rvert \le 17$。
- Subtask 5（10 Points）：$18 \le \lvert T\rvert \le 77$。
- Subtask 6（12 Points）：$\lvert T\rvert = 1326$。
- Subtask 7（20 Points）：$q \le 500$，$\lvert T\rvert \le 600$。
- Subtask 8（26 Points）：无特殊性质。

对于所有数据，保证 $1 \le q \le 5000$，$1 \le \lvert T\rvert \le 1400$，字符串 $S$ 仅包含小写英文字母和大写英文字母。

## 解题思路

### 问题分析

凯撒加密的密钥 $k$ 有 $52$ 种可能（字母表共 $52$ 个字符：$26$ 个大写 + $26$ 个小写）。对于每个密文 $T$，只需尝试所有 $52$ 种解密偏移量，用交互库验证即可。

### 核心思路

1. 对于每个密文 $T$，依次尝试 $k = 0, 1, 2, \ldots, 51$。
2. 对当前 $k$，将 $T$ 解密得到猜测字符串 $S'$。
3. 向交互库提交 $S'$，获取匹配数。
4. 若匹配数等于 $\lvert T\rvert$，说明解密成功，进入下一组。

### 算法流程

1. 读入 $q$ 组测试。
2. 对每组测试，读入密文 $T$。
3. 从 $k=0$ 开始枚举，最多 $52$ 次：
   - 将 $T$ 按偏移量 $k$ 解密（字母表循环右移 $k$ 位的逆操作）。
   - 输出猜测并读取响应。
   - 若完全匹配则进入下一组。
4. 注意：解密时需区分大小写字母，$\texttt{z}$ 右移一位为 $\texttt{A}$，$\texttt{Z}$ 右移一位为 $\texttt{a}$。

### 复杂度分析

- 时间复杂度：$O(52 \cdot \lvert T\rvert \cdot q)$，最多 $52$ 次查询，每次处理长度为 $\lvert T\rvert$ 的字符串。
- 空间复杂度：$O(\lvert T\rvert)$。

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string caesarDecrypt(const string& s, int k) {
    string result = s;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' - k + 26) % 26;
        } else {
            c = 'a' + (c - 'a' - k + 26) % 26;
        }
    }
    return result;
}

int query(const string& guess) {
    cout << guess << endl;
    int resp;
    cin >> resp;
    if (resp == -1) {
        exit(0);
    }
    return resp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        string T;
        cin >> T;
        int len = T.length();
        string ans(len, ' ');
        int totalCorrect = 0;
        for (int k = 0; k < 52 && totalCorrect < len; k++) {
            string guess = caesarDecrypt(T, k);
            int matches = query(guess);
            if (matches == len) {
                totalCorrect = len;
                break;
            }
            totalCorrect = matches;
        }
    }
    return 0;
}
```
