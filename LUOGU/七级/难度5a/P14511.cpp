#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<vector<pair<int, int>>> points(n + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 2 * n + 2; j += 2) {
                int x, y;
                cin >> x >> y;
                points[i].push_back({x, y});
            }
        }
        
        for (int i = 1; i <= n; i++) {
            sort(points[i].begin(), points[i].end());
            cout << "1 2\n";
        }
    }
    
    return 0;
}