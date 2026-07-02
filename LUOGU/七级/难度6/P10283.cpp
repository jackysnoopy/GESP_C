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
    
    // 构建Trie树
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
    
    // 计算需要添加的最少位数
    long long ans = 0;
    
    function<void(int, int)> dfs = [&](int node, int depth) {
        if (node == -1) return;
        
        int left = trie[node].children[0];
        int right = trie[node].children[1];
        
        if (left != -1 && right != -1) {
            // 两个子树都存在，需要添加位数来区分
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