#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        vector<int> a(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }
        
        vector<stack<int>> stacks(n);
        vector<pair<int, int>> operations;
        
        // Simple greedy approach
        for (int i = 0; i < m; i++) {
            // Find a stack to put the card
            int target = -1;
            
            // Check if top of any stack matches
            for (int s = 0; s < n; s++) {
                if (!stacks[s].empty() && stacks[s].top() == a[i]) {
                    target = s;
                    break;
                }
            }
            
            if (target != -1) {
                // Put on matching stack, they will be removed
                operations.push_back({1, target + 1});
                stacks[target].pop();
            } else {
                // Find empty or suitable stack
                for (int s = 0; s < n; s++) {
                    if (stacks[s].empty()) {
                        target = s;
                        break;
                    }
                }
                
                if (target == -1) {
                    target = 0; // Use first stack
                }
                
                operations.push_back({1, target + 1});
                stacks[target].push(a[i]);
            }
        }
        
        cout << operations.size() << "\n";
        for (auto& op : operations) {
            cout << op.first << " " << op.second << "\n";
        }
    }
    
    return 0;
}