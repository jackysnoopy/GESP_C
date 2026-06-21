#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];
    vector<vector<int>> cnt(n, vector<int>(m, 0));
    int base = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '#') continue;
            int bad = 0;
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (g[ni][nj] == '#') bad++;
            }
            cnt[i][j] = bad;
            if (bad == 0) base++;
        }
    }
    int extra = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != '#') continue;
            int cur = 0;
            bool self_ok = true;
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (g[ni][nj] != '.') self_ok = false;
                if (g[ni][nj] == '.' && cnt[ni][nj] == 1) cur++;
            }
            if (self_ok) cur++;
            if (cur > extra) extra = cur;
        }
    }
    cout << base + extra << "\n";
    return 0;
}
