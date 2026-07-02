#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Interactive problem - GCJ 2021 #1B Digit Blocks
    // This is a placeholder solution
    
    int T, N, B;
    long long P;
    cin >> T >> N >> B >> P;
    
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < N * B; i++) {
            int D;
            cin >> D;
            
            // Simple strategy: place on tower (i % N) + 1
            cout << (i % N) + 1 << endl;
            cout.flush();
        }
    }
    
    // Read final verdict
    int verdict;
    cin >> verdict;
    
    return 0;
}
