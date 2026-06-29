#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> claims(n);
    for (int i = 0; i < n; i++) {
        cin >> claims[i].first >> claims[i].second;
    }
    
    // Count how many people claim to be at each rank
    vector<int> count(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        int a = claims[i].first;
        int b = claims[i].second;
        
        // If a + b >= n, the claim is invalid
        if (a + b >= n) continue;
        
        // The person claims to be at rank a + 1 (0-indexed: a)
        int rank = a + 1;
        if (rank >= 1 && rank <= n) {
            count[rank]++;
        }
    }
    
    // For each rank, at most one person can be telling the truth
    int truth = 0;
    for (int i = 1; i <= n; i++) {
        truth += min(count[i], 1);
    }
    
    cout << n - truth << "\n";
    return 0;
}
