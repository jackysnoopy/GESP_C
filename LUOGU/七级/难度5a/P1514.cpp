#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 引水入城：DFS + 区间覆盖
// 1. 对第一行每个城市 DFS，记录其能覆盖的最后一行的左右端点 [L,R]
// 2. 检查最后一行是否每个城市都能被覆盖：若有未覆盖城市，输出 0 + 数量
// 3. 否则用区间覆盖贪心选最少蓄水厂

int N, M;
vector<vector<int>> h;
vector<vector<int>> L, R; // 每个格子能覆盖最后一行的范围
vector<vector<bool>> visited;

void dfs(int x, int y) {
    if (visited[x][y]) return;
    visited[x][y] = true;
    if (x == N - 1) {
        L[x][y] = R[x][y] = y;
    } else {
        L[x][y] = INT_MAX;
        R[x][y] = INT_MIN;
    }
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (h[nx][ny] >= h[x][y]) continue; // 只能往低处
        dfs(nx, ny);
        L[x][y] = min(L[x][y], L[nx][ny]);
        R[x][y] = max(R[x][y], R[nx][ny]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    h.assign(N, vector<int>(M));
    L.assign(N, vector<int>(M, 0));
    R.assign(N, vector<int>(M, 0));
    visited.assign(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> h[i][j];
    
    // 从第一行的每个点 DFS
    for (int j = 0; j < M; j++) dfs(0, j);
    
    // 检查最后一行是否能全部覆盖
    vector<bool> covered(M, false);
    for (int j = 0; j < M; j++) {
        // 若 (N-1,j) 被任何第一行点覆盖
        // 等价于：(N-1,j) 自身可达（即 visited[N-1][j]）
        if (visited[N-1][j]) covered[j] = true;
    }
    int uncov = 0;
    for (int j = 0; j < M; j++) if (!covered[j]) uncov++;
    if (uncov > 0) {
        cout << 0 << "\n" << uncov << "\n";
        return 0;
    }
    
    // 区间覆盖：从第一行各点收集 [L, R]
    vector<pair<int,int>> intervals;
    for (int j = 0; j < M; j++) {
        if (L[0][j] != INT_MAX)
            intervals.push_back({L[0][j], R[0][j]});
    }
    // 按左端点排序
    sort(intervals.begin(), intervals.end());
    int cur = 0, ans = 0;
    int idx = 0;
    while (cur < M) {
        int best = -1;
        while (idx < (int)intervals.size() && intervals[idx].first <= cur) {
            best = max(best, intervals[idx].second);
            idx++;
        }
        if (best < cur) {
            // 不可能发生，因为前面已经检查过覆盖
            ans = -1;
            break;
        }
        cur = best + 1;
        ans++;
    }
    cout << 1 << "\n" << ans << "\n";
    return 0;
}
