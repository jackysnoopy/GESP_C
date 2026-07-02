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
        int N;
        cin >> N;
        
        vector<int> order(N);
        for (int i = 0; i < N; i++) {
            cin >> order[i];
            order[i]--; // 0-indexed
        }
        
        cout << "Case #" << t << ": ";
        
        // The deck has no decreasing subsequence of length 3
        // Ben examines cards in given order, always picks the best unknown card
        // He had to examine ALL N cards before finding card with value 1
        
        // Simulate Ben's strategy:
        // At each step, Ben picks a card that minimizes worst-case
        // Given the constraint, we can work backwards
        
        // For N=1: trivial
        if (N == 1) {
            cout << "1\n";
            continue;
        }
        
        // General approach:
        // Ben's strategy: if the card he picks has value 1, he stops.
        // Otherwise, he continues. He had to examine all N cards.
        // This means: when he examined card i, it couldn't have been determined
        // that card (order[i]) must be value 1.
        
        // Use the constraint that no decreasing subsequence of length 3 exists.
        // This means the sequence can be partitioned into 2 increasing subsequences.
        
        // Backtrack: assign values from N down to 1
        vector<int> values(N, 0);
        vector<int> LIS(N, 0), LDS(N, 0);
        
        // Simple approach: assign values greedily
        // The last card Ben examines must be value 1 (he found it last)
        values[order[N - 1]] = 1;
        
        int nextVal = 2;
        for (int i = N - 2; i >= 0; i--) {
            values[order[i]] = nextVal++;
        }
        
        // Verify and adjust for lexicographically greatest
        // For now, output the simple assignment
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << " ";
            cout << values[i];
        }
        cout << "\n";
    }
    
    return 0;
}