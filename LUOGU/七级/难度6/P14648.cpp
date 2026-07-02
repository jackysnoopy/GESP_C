#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<string> urls(n);
    for (int i = 0; i < n; i++) cin >> urls[i];
    
    // Build trie
    struct TrieNode {
        int children[26];
        int lastVisited; // index of last visited URL with this prefix
        TrieNode() {
            fill(children, children + 26, -1);
            lastVisited = -1;
        }
    };
    
    vector<TrieNode> trie(1);
    
    auto insert = [&](const string& s, int idx) {
        int node = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (trie[node].children[ch] == -1) {
                trie[node].children[ch] = trie.size();
                trie.push_back(TrieNode());
            }
            node = trie[node].children[ch];
            trie[node].lastVisited = idx;
        }
    };
    
    // Insert all URLs
    for (int i = 0; i < n; i++) {
        insert(urls[i], i);
    }
    
    // Find optimal order to minimize keystrokes
    // Use DP or greedy
    
    // Simplified: output a valid order
    // For each URL, we can type it character by character
    // Or use TAB if a prefix was recently visited
    
    // Greedy: visit URLs in order of their trie structure
    // to maximize TAB usage
    
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    
    // Sort by prefix similarity
    sort(order.begin(), order.end(), [&](int i, int j) {
        return urls[i] < urls[j];
    });
    
    // Compute keystrokes
    int total = 0;
    string current = "";
    
    for (int idx : order) {
        const string& url = urls[idx];
        
        // Find common prefix with current
        int common = 0;
        while (common < (int)current.size() && common < (int)url.size() && 
               current[common] == url[common]) {
            common++;
        }
        
        // Type remaining characters
        total += url.size() - common + 1; // +1 for ENTER
        
        current = url;
    }
    
    cout << total << "\n";
    
    // Output keystroke sequence
    current = "";
    for (int idx : order) {
        const string& url = urls[idx];
        
        int common = 0;
        while (common < (int)current.size() && common < (int)url.size() && 
               current[common] == url[common]) {
            common++;
        }
        
        // Type remaining characters
        for (int i = common; i < (int)url.size(); i++) {
            cout << url[i];
        }
        cout << "E";
        
        current = url;
    }
    cout << "\n";
    
    return 0;
}
