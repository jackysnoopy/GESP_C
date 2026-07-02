#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        vector<string> maze(n, string(m, '.'));
        
        maze[0][0] = 'x';
        
        int placed = 0;
        for (int i = 0; i < n && placed < k; i++) {
            for (int j = 0; j < m && placed < k; j++) {
                if (i == 0 && j == 0) continue;
                if (placed < k) {
                    maze[i][j] = 'o';
                    placed++;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << maze[i] << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}
