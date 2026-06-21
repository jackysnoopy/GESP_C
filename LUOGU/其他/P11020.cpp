#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<string> grid(n, string(m, '.'));
        int placed = 0;
        for (int i = 0; i < n && placed < k; i++) {
            for (int j = 0; j < m && placed < k; j++) {
                if ((i + j) % 2 == 0) {
                    grid[i][j] = 'S';
                    placed++;
                }
            }
        }
        for (int i = 0; i < n && placed < k; i++) {
            for (int j = 0; j < m && placed < k; j++) {
                if (grid[i][j] == '.') {
                    grid[i][j] = 'S';
                    placed++;
                }
            }
        }
        for (int i = 0; i < n; i++) cout << grid[i] << "\n";
    }
    return 0;
}
