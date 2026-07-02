#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<string> board(n);
    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }
    
    vector<int> results;
    
    for (int day = 0; day <= q; day++) {
        if (day > 0) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            if (board[x][y] == 'F') {
                board[x][y] = '.';
            } else {
                board[x][y] = 'F';
            }
        }
        
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> que;
        
        dist[0][0] = 0;
        que.push({0, 0});
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        while (!que.empty()) {
            int x = que.front().first;
            int y = que.front().second;
            que.pop();
            
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && 
                    board[nx][ny] != '#' && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    que.push({nx, ny});
                }
            }
        }
        
        int maxDist = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'F' && dist[i][j] != -1) {
                    maxDist = max(maxDist, dist[i][j]);
                }
            }
        }
        
        results.push_back(maxDist);
    }
    
    for (int res : results) {
        cout << res << "\n";
    }
    
    return 0;
}