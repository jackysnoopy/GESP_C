#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    char line[256];
    int t;
    cin >> t;
    cin.ignore();
    bool first = true;
    while (t--) {
        if (!first) cout << endl;
        first = false;
        int r, c;
        cin >> r >> c;
        cin.ignore();
        char grid[31][81];
        for (int i = 0; i < r; i++) {
            cin.getline(grid[i], 81);
        }
        bool visited[31][81];
        memset(visited, 0, sizeof(visited));
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int islands = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (!visited[i][j] && grid[i][j] == '#') {
                    islands++;
                    vector<pair<int,int>> stk;
                    stk.push_back({i, j});
                    visited[i][j] = true;
                    while (!stk.empty()) {
                        int x = stk.back().first, y = stk.back().second;
                        stk.pop_back();
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx >= 0 && nx < r && ny >= 0 && ny < c && !visited[nx][ny] && grid[nx][ny] == '#') {
                                visited[nx][ny] = true;
                                stk.push_back({nx, ny});
                            }
                        }
                    }
                }
            }
        }
        cout << islands << endl;
    }
    return 0;
}
