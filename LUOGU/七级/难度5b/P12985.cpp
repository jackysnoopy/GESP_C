#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Interactive problem - GCJ 2022 #1A Equal Sum
    // This is a placeholder solution
    
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        
        // Output our chosen numbers
        for (int i = 1; i <= N; i++) {
            cout << i * 2 << (i < N ? " " : "\n");
        }
        cout.flush();
        
        // Read the judge's numbers
        vector<int> B(N);
        for (int i = 0; i < N; i++) {
            cin >> B[i];
        }
        
        // Output a partition
        // Simple strategy: put first N numbers in first subset
        for (int i = 1; i <= N; i++) {
            cout << i * 2 << (i < N ? " " : "\n");
        }
        cout.flush();
    }
    
    return 0;
}
