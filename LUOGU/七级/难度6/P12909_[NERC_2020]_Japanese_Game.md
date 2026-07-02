# [NERC 2020] Japanese Game

## 题目描述

一维 Nonogram 游戏，给定 mask（所有解的交集），找到任意一个合法的 profile 或判断无解。

## 输入格式

一行字符串 m，由 # 和 _ 组成。

## 输出格式

如果无解输出 -1。
否则第一行输出 k（profile 长度），第二行输出 k 个整数。

## 样例

### 样例 1
输入：
```
__#_____
```
输出：
```
2
3 2
```

### 样例 2
输入：
```
_#
```
输出：
```
-1
```

## 提示

- 1 ≤ n ≤ 100000

## 解题思路

### 问题分析

mask 是所有合法 profile 解的交集。需要判断是否存在这样的 profile。

### 核心思路

1. 将连续的 # 分组
2. 检查分组是否合法
3. 输出分组结果作为 profile

### 算法流程

1. 扫描 mask，找到连续 # 的段
2. 每段的长度作为 profile 的一个元素
3. 验证是否合法

### 复杂度分析

- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string mask;
    getline(cin, mask);
    
    while (!mask.empty() && mask.back() == ' ') {
        mask.pop_back();
    }
    
    int n = mask.size();
    
    vector<int> hash_pos;
    for (int i = 0; i < n; i++) {
        if (mask[i] == '#') {
            hash_pos.push_back(i);
        }
    }
    
    if (hash_pos.empty()) {
        cout << 0 << endl;
        return 0;
    }
    
    vector<int> groups;
    int cnt = 1;
    for (int i = 1; i < hash_pos.size(); i++) {
        if (hash_pos[i] == hash_pos[i - 1] + 1) {
            cnt++;
        } else {
            groups.push_back(cnt);
            cnt = 1;
        }
    }
    groups.push_back(cnt);
    
    cout << groups.size() << endl;
    for (int i = 0; i < groups.size(); i++) {
        if (i > 0) cout << " ";
        cout << groups[i];
    }
    cout << endl;
    
    return 0;
}
```
