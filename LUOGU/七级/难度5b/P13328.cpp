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
        int N;
        cin >> N;
        
        vector<int> L(N), P(N);
        for (int i = 0; i < N; i++) cin >> L[i];
        for (int i = 0; i < N; i++) cin >> P[i];
        
        // Sort by P_i/L_i descending (play most dangerous first)
        // Use comparison: P[i]*L[j] > P[j]*L[i]
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            long long left = (long long)P[a] * L[b];
            long long right = (long long)P[b] * L[a];
            if (left != right) return left > right;
            return a < b;
        });
        
        cout << "Case #" << t << ":";
        for (int i = 0; i < N; i++) cout << " " << idx[i];
        cout << "\n";
    }
    
    return 0;
}