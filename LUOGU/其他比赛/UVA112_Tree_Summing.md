# UVA112 - Tree Summing (树求和)

## 题目描述

给定一棵二叉树和一个目标和，判断是否存在从根节点到叶节点的路径，使得路径上所有节点值的和等于目标值。

## 输入格式

每个测试用例首先输入目标和，然后以括号表示法输入二叉树，格式如 (L()R)，空节点表示为 ()。每个测试用例以分号结束。

## 输出格式

如果存在满足条件的路径，输出 "yes"，否则输出 "no"。

## 样例

输入：
```
5
(;7;left;left);5
22
(;7;left;left)
```

输出：
```
yes
no
```

## 解题思路

### 问题分析

需要遍历二叉树的所有根到叶路径，检查是否存在某条路径的节点值之和等于目标值。树的输入格式为括号表示法，需要解析。

### 核心思路

使用深度优先搜索（DFS）遍历二叉树，在遍历过程中累加路径上的节点值。当到达叶节点时，检查当前路径和是否等于目标值。

### 算法流程

1. 解析括号表示法，构建二叉树
2. 使用 DFS 遍历二叉树
3. 在遍历过程中累加路径和
4. 到达叶节点时检查是否等于目标值
5. 输出结果并释放内存

### 复杂度分析

- 时间复杂度：O(n)，其中 n 是树中节点的数量
- 空间复杂度：O(h)，其中 h 是树的高度，递归调用栈的空间

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <functional>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int target;
    while (cin >> target) {
        cin.ignore();
        string line;
        getline(cin, line);
        
        if (line.empty()) {
            cout << "no\n";
            continue;
        }
        
        int pos = 0;
        
        function<TreeNode*()> buildTree = [&]() -> TreeNode* {
            while (pos < line.size() && line[pos] != '(') pos++;
            if (pos >= line.size()) return nullptr;
            
            pos++;
            if (line[pos] == ')') {
                return nullptr;
            }
            
            bool negative = false;
            if (line[pos] == '-') {
                negative = true;
                pos++;
            }
            
            int num = 0;
            while (pos < line.size() && isdigit(line[pos])) {
                num = num * 10 + (line[pos] - '0');
                pos++;
            }
            
            TreeNode* node = new TreeNode(negative ? -num : num);
            node->left = buildTree();
            node->right = buildTree();
            
            while (pos < line.size() && line[pos] != ')') pos++;
            if (pos < line.size()) pos++;
            
            return node;
        };
        
        TreeNode* root = buildTree();
        
        bool found = false;
        
        function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int currentSum) {
            if (!node || found) return;
            
            currentSum += node->val;
            
            if (!node->left && !node->right) {
                if (currentSum == target) {
                    found = true;
                }
                return;
            }
            
            dfs(node->left, currentSum);
            dfs(node->right, currentSum);
        };
        
        dfs(root, 0);
        cout << (found ? "yes" : "no") << "\n";
        
        function<void(TreeNode*)> deleteTree = [&](TreeNode* node) {
            if (!node) return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        };
        deleteTree(root);
    }
    
    return 0;
}
```
