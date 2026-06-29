#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    string source = "";
    string target = "";
    
    // Read source string
    string line;
    getline(cin, line); // consume newline
    while ((int)source.size() < n) {
        getline(cin, line);
        source += line;
    }
    
    // Read target string
    while ((int)target.size() < m) {
        getline(cin, line);
        target += line;
    }
    
    // Greedy: find longest prefix of target that appears in source
    int cuts = 0;
    int target_pos = 0;
    
    while (target_pos < m) {
        // Find the longest substring starting at target_pos that appears in source
        int max_len = 0;
        int best_start = -1;
        
        for (int i = 0; i < n; i++) {
            int len = 0;
            while (i + len < n && target_pos + len < m && source[i + len] == target[target_pos + len]) {
                len++;
            }
            if (len > max_len) {
                max_len = len;
                best_start = i;
            }
        }
        
        if (max_len == 0) {
            // Need to cut a single character
            cuts++;
            target_pos++;
        } else {
            // Use the longest match
            cuts++;
            target_pos += max_len;
        }
    }
    
    cout << cuts << "\n";
    return 0;
}
