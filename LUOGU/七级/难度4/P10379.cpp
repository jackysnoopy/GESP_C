#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    set<set<pair<int,int>>> shapes;
    
    for (int si = 0; si < n; si++) {
        for (int sj = 0; sj < m; sj++) {
            if (vis[si][sj]) continue;
            int col = a[si][sj];
            vector<pair<int,int>> cells;
            vector<int> qr, qc;
            qr.push_back(si); qc.push_back(sj);
            vis[si][sj] = true;
            for (int i = 0; i < (int)qr.size(); i++) {
                int x = qr[i], y = qc[i];
                cells.push_back({x, y});
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && a[nx][ny] == col) {
                        vis[nx][ny] = true;
                        qr.push_back(nx); qc.push_back(ny);
                    }
                }
            }
            int minR = cells[0].first, minC = cells[0].second;
            for (int i = 0; i < (int)cells.size(); i++) {
                minR = min(minR, cells[i].first);
                minC = min(minC, cells[i].second);
            }
            set<pair<int,int>> shape;
            for (int i = 0; i < (int)cells.size(); i++) {
                shape.insert({cells[i].first - minR, cells[i].second - minC});
            }
            shapes.insert(shape);
        }
    }
    
    cout << shapes.size() << "\n";
    return 0;
}
