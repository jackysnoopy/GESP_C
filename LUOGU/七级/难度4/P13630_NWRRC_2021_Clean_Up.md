# [NWRRC 2021] Clean Up!

## 题目描述

Once Charlie decided to start a new life by deleting all files in his Downloads directory. It's easy to do that using $\texttt{bash}$ shell! It has two useful features: the $\texttt{rm}$ command, which removes all files given as arguments, and patterns, which are replaced with the list of files matching them before executing the command.

Charlie ran $\texttt{rm *}$, but received an $\texttt{Argument list too long}$ response. Unfortunately, after $\texttt{bash}$ replaced $\texttt{*}$ with the names of all files in the Downloads directory, it failed to run the command because it had too many arguments.

After some experiments, Charlie realized he can execute $\texttt{rm abc*}$ to delete all files with names starting with $\texttt{abc}$ if there are at most $k$ such files. If more than $k$ files match this pattern, none of them will be deleted. Of course, he can replace $\texttt{abc}$ with any string.

Help Charlie to find the smallest number of $\texttt{rm}$ commands needed to delete all files. Assume that he can only use the $\texttt{rm}$ command as $\texttt{rm *}$, where $\texttt{}$ consists of lowercase English letters (and can be empty).

## 输入格式

The first line contains two integers $n$ and $k$ --- the number of files to delete, and the maximum number of files that can be deleted by one $\texttt{rm}$ command ($1 \le n, k \le 3 \cdot 10^5$).

Each of the next $n$ lines contains a single string, denoting a file name. All file names are distinct, non-empty, and consist of lowercase English letters. The total length of all file names doesn't exceed $3 \cdot 10^5$.

## 输出格式

Print a single integer --- the smallest number of $\texttt{rm}$ commands needed to delete all files.

## 样例

### 样例输入 1
```
4 2
a
abc
abd
b
```

### 样例输出 1
```
2
```

### 样例输入 2
```
4 2
d
c
ab
a
```

### 样例输出 2
```
2
```

### 样例输入 3
```
5 3
please
remove
all
these
files
```

### 样例输出 3
```
3
```

## 提示

In the first example test, Charlie can execute $\texttt{rm ab*}$ to delete files $\texttt{abc}$ and $\texttt{abd}$, and then execute $\texttt{rm~*}$ to delete files $\texttt{a}$ and $\texttt{b}$. Note that he can't just run $\texttt{rm *}$ immediately, because initially all four files match an empty prefix.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<string> files(n);
    for (int i = 0; i < n; i++) cin >> files[i];

    sort(files.begin(), files.end());

    int ans = 0;
    int i = 0;

    while (i < n) {
        ans++;
        string prefix = "";
        int count = 0;

        for (int j = i; j < n && count < k; j++) {
            if (files[j].substr(0, prefix.size()) == prefix) {
                count++;
            } else {
                break;
            }
        }

        if (count >= k) {
            i += count;
        } else {
            i++;
        }
    }

    cout << ans << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
给定 $n$ 个文件名和参数 $k$，每次可以使用 `rm prefix*` 删除所有以 `prefix` 开头的文件，但如果匹配的文件数超过 $k$，则一个都不会被删除。要求用最少的命令删除所有文件。

### 核心思路
采用贪心策略：将文件名按字典序排序后，每次尽可能多地删除连续的、共享相同前缀的文件。由于空前缀匹配所有文件，代码实际以 $k$ 为单位批量删除文件。当剩余文件数不足 $k$ 个时，每次只删除一个文件，逐步消耗剩余文件。

### 算法流程
1. 将所有文件名按字典序排序
2. 从第一个未删除的文件开始，用空前缀尝试匹配后续文件，最多匹配 $k$ 个
3. 若匹配数 $\geq k$，则一次性删除 $k$ 个文件，指针前进 $k$ 步
4. 若匹配数 $< k$（剩余不足 $k$ 个文件），则每次只删除 $1$ 个文件，指针前进 $1$ 步
5. 重复上述过程直到所有文件被删除，统计总共使用的命令数

### 复杂度分析
- **时间复杂度**：$O(n \log n)$，排序占主导，贪心扫描为 $O(n)$
- **空间复杂度**：$O(n)$，存储文件名数组
