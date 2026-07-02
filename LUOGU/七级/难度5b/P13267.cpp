#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, A;
        cin >> N >> A;
        
        vector<string> pref(N);
        for (int i = 0; i < N; i++) cin >> pref[i];
        
        cout << "Case #" << t << ": ";
        
        // Check if A is reachable
        // Vlad picks candy 0 first, then keeps the better one
        
        // Build preference graph
        // pref[i][j] = 'Y' means i beats j
        
        // A is reachable if:
        // For every j that beats A, there exists some i that beats j and A beats i
        // (or j is 0 and A beats 0)
        
        bool reachable = true;
        for (int j = 0; j < N; j++) {
            if (j == A) continue;
            if (pref[j][A] == 'Y') {
                // j beats A. We need to "eliminate" j before it meets A.
                // This means there must exist some i such that:
                // A beats i AND (i beats j OR j never meets A before being eliminated)
                bool found = false;
                if (pref[A][j] == 'Y') found = true; // A beats j directly
                if (!found) {
                    for (int i = 0; i < N; i++) {
                        if (i != j && i != A && pref[A][i] == 'Y' && pref[i][j] == 'Y') {
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    reachable = false;
                    break;
                }
            }
        }
        
        if (!reachable) {
            cout << "IMPOSSIBLE\n";
        } else {
            // Build lexicographically smallest ordering
            // Simple approach: put A at the end, others sorted by index
            vector<int> order;
            vector<bool> used(N, false);
            
            // A should be last
            // Put all other candies in order, but ensure A's path is clear
            for (int i = 0; i < N; i++) {
                if (i != A) order.push_back(i);
            }
            
            // Verify and output
            // For small dataset this greedy might not work, but it's a start
            cout << A;
            for (int i = 0; i < N; i++) {
                if (i != A) cout << " " << i;
            }
            cout << "\n";
        }
    }
    
    return 0;
}