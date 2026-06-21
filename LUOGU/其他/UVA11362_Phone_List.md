# Phone List

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2347

[PDF](https://uva.onlinejudge.org/external/113/p11362.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/86a9ad22547794c86c707c6301a3959ca76cfd43.png)

## 输入格式
![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/d5bf45fcc4bdcc7e676e655a36dda7a794b189af.png)

## 输出格式
![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/da40d07a03794e91297b87d8a38934cf0ee2e2e4.png)

## 样例
### 样例 1
```
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346
```
```
NO
YES
```

## 解题思路
### 问题分析
判断号码列表中是否有某个号码是另一个的前缀。

### 核心思路
Trie 树。插入时标记结尾，检查路径上是否有结尾标记。

### 算法流程
1. 读入 n 和号码
2. 构建 Trie
3. 每个号码插入前检查路径上是否有终点
4. 插入后检查是否有号码是它的前缀

### 复杂度分析
- 时间复杂度：O(总位数)
- 空间复杂度：O(总位数)

## 参考代码
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 100005;
int trie[MAXN][10], tot;
bool end_mark[MAXN];

bool insert(const string& s) {
    int p = 0;
    for (char c : s) {
        int idx = c - '0';
        if (!trie[p][idx]) trie[p][idx] = ++tot;
        p = trie[p][idx];
        if (end_mark[p]) return false;
    }
    // 检查是否有号码是它的前缀
    for (int i = 0; i < 10; i++)
        if (trie[p][i]) return false;
    end_mark[p] = true;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        memset(trie, 0, sizeof(trie));
        memset(end_mark, 0, sizeof(end_mark));
        tot = 0;
        
        int n; cin >> n;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            if (ok && !insert(s)) ok = false;
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
```
