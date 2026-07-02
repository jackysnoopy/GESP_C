# [USACO24OPEN] Identity Theft P

## 题目描述

Farmer John 的 N 头牛每头都有一个 Farm ID 号（位串形式）。当 Bessie 问一头牛它的 ID 号时，它会开始说出正确的位串，但可能在完成之前就停下来。如果 Bessie 听到的位串不是任何牛的 ID 号，她会耸耸肩走开。但如果它是另一头牛的 ID 号，就会触发 lockdown。Farmer John 想通过在 ID 号末尾添加一些位来防止这种情况发生。求最少需要多少秒。

## 输入格式

第一行包含 N，表示牛的数量。
接下来 N 行，每行一个位串，表示第 k 头牛的 Farm ID 号。

## 输出格式

输出 Farmer John 需要花费的最少秒数。

## 样例

### 样例 1
输入：
```
3
1
1
1
```
输出：
```
5
```

### 样例 2
输入：
```
3
1
11
111
```
输出：
```
2
```

## 提示

所有 Farm ID 号的总长度不超过 10^6。

## 解题思路

### 问题分析
需要在 ID 号末尾添加位数，使得任何前缀都不是其他牛的完整 ID 号。

### 核心思路
使用 Trie 树构建所有 ID 号，然后计算需要添加的最少位数。

### 算法流程
1. 将所有 ID 号插入 Trie 树
2. 遍历 Trie 树，计算每个节点的子树大小
3. 当一个节点有两个子节点时，需要添加位数来区分

### 复杂度分析
- 时间复杂度：O(总长度)
- 空间复杂度：O(总长度)

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    
    vector<string> ids(n);
    for (int i = 0; i < n; i++) {
        cin >> ids[i];
    }
    
    struct TrieNode {
        int children[2];
        int count;
        TrieNode() {
            children[0] = children[1] = -1;
            count = 0;
        }
    };
    
    vector<TrieNode> trie(1);
    
    for (const string& s : ids) {
        int node = 0;
        for (char c : s) {
            int bit = c - '0';
            if (trie[node].children[bit] == -1) {
                trie[node].children[bit] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].children[bit];
            trie[node].count++;
        }
    }
    
    long long ans = 0;
    
    function<void(int, int)> dfs = [&](int node, int depth) {
        if (node == -1) return;
        
        int left = trie[node].children[0];
        int right = trie[node].children[1];
        
        if (left != -1 && right != -1) {
            ans += trie[left].count * trie[right].count;
            dfs(left, depth + 1);
            dfs(right, depth + 1);
        } else if (left != -1) {
            dfs(left, depth + 1);
        } else if (right != -1) {
            dfs(right, depth + 1);
        }
    };
    
    dfs(0, 0);
    
    printf("%lld\n", ans);
    return 0;
}
```