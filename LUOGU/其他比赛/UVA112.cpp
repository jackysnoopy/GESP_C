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
        
        size_t pos = 0;
        
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
