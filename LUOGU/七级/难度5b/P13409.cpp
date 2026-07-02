#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        long long k, C;
        cin >> k >> C;
        
        cout << "Case #" << t << ": ";
        
        if (k == 1) {
            // Only 1 person, need ceil(C/1) + ... = C boxes
            // Actually: person can buy any amount 1..C
            // We need enough boxes to give any amount 1..C
            // With boxes of sizes that can combine to any value 1..C
            // Optimal: binary representation
            // Need ceil(log2(C+1)) boxes
            long long ans = 0;
            long long sum = 1;
            while (sum <= C) {
                ans++;
                sum *= 2;
            }
            cout << ans << "\n";
        } else {
            // For k >= 2: more complex
            // The key insight: for k=2, C=2, answer=3
            // We need boxes that can serve any sequence of k orders
            
            // General: need to partition into groups
            // Each group can serve one person's order
            // But we don't know future orders
            
            // For k people, C max per person:
            // The answer relates to the number of "digits" needed
            
            long long ans = 0;
            if (C <= 2) {
                ans = 2 * k + 1;
            } else if (C <= 3) {
                ans = 2 * k + 1;
            } else {
                // Binary approach: need enough boxes to represent any number 1..C
                // and enough copies for k people
                long long bits = 0;
                long long sum = 1;
                while (sum <= C) {
                    bits++;
                    sum *= 2;
                }
                ans = bits * k + 1;
            }
            
            cout << ans << "\n";
        }
    }
    
    return 0;
}