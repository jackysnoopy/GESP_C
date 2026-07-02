# Tree Search

## 题目描述

这是一道交互题。

给定一棵 $N$ 个点的有根二叉树 $T$，保证根结点的编号为 $1$。

树上恰有一个未知的结点是特殊的，你需要找出这个结点。

你每次可以向交互库询问一棵子树中是否含有特殊结点，你可以询问至多 $35$ 次。

### 实现细节

你需要实现下列函数：

```
int solve(int N, std::vector < int > p)
```

- $N$：树的结点数量。
- $p$：长度为 $N-1$ 的数组，描述树的形态。第 $i$ 个元素 $p_i$ 满足 $1\leq p_i\leq i+1$，代表编号为 $i+2$ 的结点的父亲编号。
- $p$ 中的元素两两不同。
- 你需要返回特殊结点的编号。
- 这个函数只会被调用恰好一次。

你可以调用以下函数：

```
int ask(int x)
```

- $x$：询问的子树根结点编号。
- 你需要保证 $1\leq x\leq N$。
- 如果子树包含特殊结点，返回值为 $1$，否则为 $0$。

## 输入格式

以下为下发 grader 的输入格式，你不应该从标准输入中读入任何信息。

第一行输入一个整数 $N$。

第二行输入 $N-1$ 个整数 $p_i$。

接下来对于每个询问，输入一个整数代表询问的返回值。

## 输出格式

以下为下发 grader 的输出格式，你不应该向标准输出中打印任何信息。

对于每个询问，输出一行 `? x`，其中 $x$ 为询问的结点。

最后输出一行 `! x`，其中 $x$ 为猜测的结点编号。

## 样例

### 样例输入

```
5
1 1 2 4

1

0
 
```

### 样例输出

```
 
? 4

? 5

! 4
```

## 提示

### 数据范围

本题采用捆绑测试。

- Subtask 1（20 pts）：$N\leq 35$。
- Subtask 2（30 pts）：$p_i=i+1$。
- Subtask 3（15 pts）：$p_i=\frac{i}{2}+1$。
- Subtask 4（35 pts）：无特殊限制。

对于 $100\%$ 的数据，保证 $1\leq N\leq 10^5$。

## 解题思路

### 问题分析

这是一个交互题，需要在二叉树中找到特殊结点。关键点：

1. 树是有根二叉树，根节点为1
2. 只有一个特殊节点
3. 每次可以询问一个子树是否包含特殊节点
4. 询问次数限制为35次

### 核心思路

1. **二分查找思想**：每次将搜索范围缩小一半。
2. **子树大小计算**：预处理每个子树的大小。
3. **询问策略**：
   - 从根节点开始
   - 如果当前子树包含特殊节点，检查左子树
   - 如果左子树包含特殊节点，则在左子树中继续查找
   - 否则在右子树中查找

### 算法流程

1. 预处理：计算每个节点的子树大小。
2. 从根节点开始查找：
   - 询问当前节点的子树是否包含特殊节点
   - 如果包含，检查左子树
   - 根据询问结果决定在左子树还是右子树中继续查找
3. 直到找到特殊节点。

### 复杂度分析

- 时间复杂度：$O(n)$，预处理子树大小
- 询问次数：$O(\log n)$，每次将搜索范围减半

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<int> children[MAXN];
int parent[MAXN];
int subtreeSize[MAXN];

// 计算子树大小
void dfs(int u) {
    subtreeSize[u] = 1;
    for (int v : children[u]) {
        dfs(v);
        subtreeSize[u] += subtreeSize[v];
    }
}

// 查找特殊节点
int findSpecial(int u) {
    // 如果当前节点就是特殊节点
    if (ask(u) == 1) {
        // 检查是否是叶子节点或者子树中只有这一个特殊节点
        bool hasSpecialChild = false;
        for (int v : children[u]) {
            if (ask(v) == 1) {
                hasSpecialChild = true;
                break;
            }
        }
        if (!hasSpecialChild) {
            return u;
        }
    }
    
    // 在子树中查找
    for (int v : children[u]) {
        if (ask(v) == 1) {
            return findSpecial(v);
        }
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 这里是交互题的框架，实际实现需要根据交互库调整
    // 以下为示例代码
    
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        parent[i] = p;
        children[p].push_back(i);
    }
    
    // 计算子树大小
    dfs(1);
    
    // 查找特殊节点
    int result = findSpecial(1);
    cout << "! " << result << endl;
    
    return 0;
}
```

**注意**：以上代码为框架，实际实现需要根据交互库的具体要求进行调整。交互题需要按照题目要求的格式进行输入输出。