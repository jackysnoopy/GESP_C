#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, l, p;
        cin >> n >> l >> p;
        
        vector<string> sentences(n);
        for (int i = 0; i < n; i++) {
            cin >> sentences[i];
        }
        
        // Compute prefix sums of sentence lengths (including spaces)
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + sentences[i].length() + 1; // +1 for space
        }
        
        // DP: dp[i] = minimum discomfort for first i sentences
        vector<long long> dp(n + 1, 1e18);
        vector<int> prev(n + 1, -1);
        dp[0] = 0;
        
        // For each sentence i, try all possible line breaks j
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                long long line_len = prefix[i] - prefix[j] - 1; // -1 for last space
                long long discomfort = 0;
                
                if (p == 1) {
                    discomfort = abs(line_len - l);
                } else if (p == 2) {
                    long long diff = line_len - l;
                    discomfort = diff * diff;
                } else {
                    discomfort = pow(abs(line_len - l), p);
                }
                
                if (dp[j] + discomfort < dp[i]) {
                    dp[i] = dp[j] + discomfort;
                    prev[i] = j;
                }
            }
        }
        
        if (dp[n] >= 1e18) {
            cout << "Too hard to arrange\n";
        } else {
            cout << dp[n] << "\n";
            
            // Reconstruct the solution
            vector<int> breaks;
            int cur = n;
            while (cur > 0) {
                breaks.push_back(cur);
                cur = prev[cur];
            }
            reverse(breaks.begin(), breaks.end());
            
            int start = 0;
            for (int idx : breaks) {
                for (int i = start; i < idx; i++) {
                    if (i > start) cout << " ";
                    cout << sentences[i];
                }
                cout << "\n";
                start = idx;
            }
        }
        
        cout << "--------------------\n";
    }
    
    return 0;
}
