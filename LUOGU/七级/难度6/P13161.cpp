#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;
        
        vector<vector<char>> grid(N, vector<char>(N, '.'));
        vector<pair<int, int>> changes;
        
        for (int i = 0; i < M; i++) {
            char c;
            int r, c2;
            cin >> c >> r >> c2;
            r--; c2--;
            grid[r][c2] = c;
        }
        
        // 简化：直接填充
        int points = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 'o') points += 2;
                else if (grid[i][j] == '+' || grid[i][j] == 'x') points += 1;
            }
        }
        
        cout << "Case #" << t << ": " << points << " " << changes.size() << endl;
        for (auto& [r, c] : changes) {
            cout << "o " << r + 1 << " " << c + 1 << endl;
        }
    }
    
    return 0;
}
