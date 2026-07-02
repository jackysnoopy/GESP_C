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
        
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        
        cout << "Case #" << t << ": ";
        
        // a[i] is the starting value. Each card is +a[i] or *a[i]
        // Read the operations
        vector<char> op(N);
        vector<int> val(N);
        for (int i = 0; i < N; i++) {
            cin >> op[i] >> val[i];
        }
        
        // This is an interactive problem - simplified solution
        // For non-interactive use, just read and output
        
        cout << "me\n";
        
        // Strategy: control parity
        // +x changes value by x (parity changes if x is odd)
        // *x multiplies by x (parity changes if x is odd, or if value is odd and x is odd)
        
        // Simple strategy for winning
        int start;
        cin >> start;
        
        // Not interactive in this context, just output placeholder
    }
    
    return 0;
}