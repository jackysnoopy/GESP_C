#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
int id, n, K;
string S[MAXN];
string T;

int main() {
    scanf("%d %d %d", &id, &n, &K);
    
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    cin >> T;
    
    int len = T.length();
    
    // 构建Trie树
    struct TrieNode {
        int children[26];
        int count;
        TrieNode() {
            for (int i = 0; i < 26; i++) children[i] = -1;
            count = 0;
        }
    };
    
    vector<TrieNode> trie(1);
    
    for (int i = 0; i < n; i++) {
        int node = 0;
        for (char c : S[i]) {
            int idx = c - 'a';
            if (trie[node].children[idx] == -1) {
                trie[node].children[idx] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].children[idx];
            trie[node].count++;
        }
    }
    
    // 计算好的三元组数量
    long long total = 0;
    vector<int> ans(len, 0);
    
    // 简化处理：对于每个位置，计算包含它的好三元组数量
    for (int i = 0; i < len; i++) {
        int cnt = 0;
        for (int j = i; j < len && cnt < K; j++) {
            // 检查T[i..j]是否是某个Si的前缀
            int node = 0;
            bool isPrefix = true;
            for (int k = i; k <= j; k++) {
                int idx = T[k] - 'a';
                if (trie[node].children[idx] == -1) {
                    isPrefix = false;
                    break;
                }
                node = trie[node].children[idx];
            }
            
            if (isPrefix && trie[node].count > 0) {
                cnt++;
                total++;
                for (int k = i; k <= j; k++) {
                    ans[k]++;
                }
            }
        }
    }
    
    printf("%lld\n", total);
    for (int i = 0; i < len; i++) {
        printf("%d%c", ans[i], i == len - 1 ? '\n' : ' ');
    }
    
    return 0;
}