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
        
        vector<int> A(N), B(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        for (int i = 0; i < N; i++) cin >> B[i];
        
        // X[i] = number of j such that A[j] <= A[i] and B[j] <= B[i]
        vector<int> X(N);
        for (int i = 0; i < N; i++) {
            int cnt = 0;
            for (int j = 0; j < N; j++) {
                if (A[j] <= A[i] && B[j] <= B[i]) cnt++;
            }
            X[i] = cnt;
        }
        
        cout << "Case #" << t << ":";
        for (int i = 0; i < N; i++) cout << " " << X[i];
        cout << "\n";
    }
    
    return 0;
}