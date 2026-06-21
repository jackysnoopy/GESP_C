#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
vector<vector<int>> h;
vector<vector<bool>> vis;
int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
void bfs(int sc) {
    queue<pair<int,int>> q;
    q.push(make_pair(0, sc));
    vis[0][sc] = true;
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if (nx>=0 && nx<n && ny>=0 && ny<m && !vis[nx][ny] && h[nx][ny] < h[x][y]) {
                vis[nx][ny] = true;
                q.push(make_pair(nx, ny));
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    h.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];
    vector<pair<int,int>> ranges;
    for (int j = 0; j < m; j++) {
        vis.assign(n, vector<bool>(m, false));
        bfs(j);
        int left = m, right = -1;
        for (int i = 0; i < m; i++)
            if (vis[n-1][i]) { left = min(left, i); right = max(right, i); }
        if (right != -1) ranges.push_back(make_pair(left, right));
    }
    vector<bool> covered(m, false);
    for (int i = 0; i < (int)ranges.size(); i++)
        for (int j = ranges[i].first; j <= ranges[i].second; j++) covered[j] = true;
    int uncov = 0;
    for (int i = 0; i < m; i++) if (!covered[i]) uncov++;
    if (uncov > 0) { cout << "0\n" << uncov << endl; }
    else {
        sort(ranges.begin(), ranges.end());
        int ans = 0, cur = 0, idx = 0;
        while (cur < m) {
            int mx = cur;
            while (idx < (int)ranges.size() && ranges[idx].first <= cur) { mx = max(mx, ranges[idx].second); idx++; }
            ans++; cur = mx + 1;
        }
        cout << "1\n" << ans << endl;
    }
    return 0;
}