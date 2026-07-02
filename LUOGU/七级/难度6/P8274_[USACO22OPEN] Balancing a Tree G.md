# [USACO22OPEN] Balancing a Tree G

## 题目描述
Farmer John 对不同奶牛品种的进化进行了广泛的研究。所得到的结果形成一棵 $N$（$2\le N\le 10^5$）个结点的有根树，编号为 $1\ldots N$，每个结点对应一个奶牛品种。对于每一个 $i\in [2,N]$，结点 $i$ 的父结点是结点 $p_i$（$1\le p_i< i$），意味着品种 $i$ 是由品种 $p_i$ 进化而来的。

树中的结点 $i$ 所关联的品种具有整数 $s_i$ 数量的斑点。定义树的「不平衡度」为所有结点对 $(i,j)$ 中 $|s_i-s_j|$ 的最大值，其中 $j$ 是 $i$ 的祖先。

Farmer John 不知道每个品种的 $s_i$ 的确切数值，但他知道这些值的下界和上界。你的任务是为每个结点分配一个整数值 $s_i \in [l_i,r_i]$（$0\le l_i\le r_i\le 10^9$），以最小化树的不平衡度。

## 输入格式
输入的第一行包含 $T$（$1\le T\le 10$），为需要独立求解的子测试用例的数量，以及一个整数 $B\in \{0,1\}$。

每个子测试用例的第一行包含 $N$，第二行包含 $N-1$ 个整数 $p_2,p_3,\ldots,p_N$。

以下 $N$ 行每行包含两个整数 $l_i$ 和 $r_i$。

## 输出格式
每个子测试用例的第一行包含最小不平衡度。

如果 $B=1$，则再输出一行，包含 $N$ 个空格分隔的整数 $s_1,s_2,\ldots, s_N$。

## 样例
### 样例1
输入:
```
3 0
3
1 1
0 100
1 1
6 7
5
1 2 3 4
6 6
1 6
1 6
1 6
5 5
3
1 1
0 10
0 1
9 10
```
输出:
```
3
1
4
```

## 提示
- 时间限制：2000ms
- 内存限制：262144KB

## 解题思路

### 问题分析
需要在树上分配值，使得任意祖先-后代对的差值最大值最小。

### 核心思路
1. 二分答案：检查是否存在分配方案使得不平衡度不超过 $mid$
2. 贪心分配：每个节点选择能使子树平衡的最优值

### 算法流程
1. 二分不平衡度
2. DFS遍历树，为每个节点选择合适的值
3. 检查是否满足所有约束

### 复杂度分析
- 时间复杂度：$O(N \log R)$，其中 $R$ 为值域范围
- 空间复杂度：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> children[MAXN];
int l[MAXN], r[MAXN];
int n;
int ans;
int s[MAXN];

void dfs(int u) {
    for (int v : children[u]) {
        dfs(v);
    }
    
    int low = l[u], high = r[u];
    while (low < high) {
        int mid = (low + high) / 2;
        
        bool valid = true;
        for (int v : children[u]) {
            if (s[v] < mid - ans || s[v] > mid + ans) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    s[u] = low;
}

bool check(int mid) {
    ans = mid;
    dfs(1);
    
    for (int i = 1; i <= n; i++) {
        if (s[i] < l[i] || s[i] > r[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, B;
    cin >> T >> B;
    
    while (T--) {
        cin >> n;
        
        for (int i = 1; i <= n; i++) {
            children[i].clear();
        }
        
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            children[p].push_back(i);
        }
        
        for (int i = 1; i <= n; i++) {
            cin >> l[i] >> r[i];
        }
        
        int low = 0, high = 1e9;
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        check(low);
        cout << low << endl;
        
        if (B == 1) {
            for (int i = 1; i <= n; i++) {
                cout << s[i] << (i == n ? "\n" : " ");
            }
        }
    }
    
    return 0;
}
```