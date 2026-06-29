# P3104 [USACO14MAR] Counting Friends G

## 思路

核心算法：图论+度序列

## 解题思路

### 问题分析
给定 n+1 个节点的度序列，判断删除每个节点后剩余的度序列是否能构成一个简单图。输出所有合法的节点编号。

### 核心思路
Erdős–Gallai 定理：对每个候选节点，移除后检查剩余度序列是否满足可图化条件（度数和为偶数且满足 Erdős–Gallai 不等式）。

### 算法流程
1. 读入 n+1 个节点的度序列
2. 对每个节点 i (0 ~ n)：
   - 移除第 i 个节点的度数
   - 检查剩余度数和是否为偶数
   - 排序后用 Erdős–Gallai 定理验证
3. 输出所有合法节点的编号（1-indexed）

### 复杂度分析
- 时间复杂度：O(n² log n)
- 空间复杂度：O(n)

```cpp

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool canFormGraph(vector<int>& degrees, int exclude) {
    int n = degrees.size();
    vector<int> remaining;
    for (int i = 0; i < n; i++) {
        if (i != exclude) {
            remaining.push_back(degrees[i]);
        }
    }
    
    int sum = accumulate(remaining.begin(), remaining.end(), 0);
    if (sum % 2 != 0) return false;
    
    sort(remaining.begin(), remaining.end(), greater<int>());
    
    // Check if the sequence is graphical using Erdős–Gallai theorem
    int total = sum;
    for (int i = 0; i < remaining.size(); i++) {
        if (remaining[i] < 0) return false;
        total -= remaining[i];
        int remaining_count = remaining.size() - i - 1;
        if (total < 0) return false;
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> degrees(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> degrees[i];
    }
    
    vector<int> valid;
    for (int i = 0; i <= n; i++) {
        if (canFormGraph(degrees, i)) {
            valid.push_back(i + 1);
        }
    }
    
    cout << valid.size() << "\n";
    for (int x : valid) {
        cout << x << "\n";
    }
    
    return 0;
}
```
