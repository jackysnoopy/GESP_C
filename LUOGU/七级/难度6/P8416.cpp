#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    
    // Simple approach: count inversions
    vector<pair<int, int>> swaps;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int target = i * n + j + 1;
            if (mat[i][j] != target) {
                // Find target and swap
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < n; y++) {
                        if (mat[x][y] == target) {
                            swaps.push_back({i * n + j, x * n + y});
                            swap(mat[i][j], mat[x][y]);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    cout << swaps.size() << endl;
    for (auto& sw : swaps) {
        int x1 = sw.first / n, y1 = sw.first % n;
        int x2 = sw.second / n, y2 = sw.second % n;
        cout << x1 + 1 << " " << y1 + 1 << " " << x2 + 1 << " " << y2 + 1 << endl;
    }
    
    return 0;
}