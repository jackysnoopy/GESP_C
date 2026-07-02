#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    cout << 'x';
                } else if (i == n - 1 && j == m - 1) {
                    cout << 'o';
                } else {
                    cout << '.';
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    return 0;
}