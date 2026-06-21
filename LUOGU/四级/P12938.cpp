#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int a[105][105];
int total[105];
int ans;
int cur_stations[105];
int cur_cnt;

bool check() {
    for (int j = 1; j < n; j++) {
        if (total[j] <= 0) return true;
    }
    return false;
}

int heuristic() {
    int h = m + 1;
    for (int j = 1; j < n; j++) {
        if (total[j] <= 0) return 0;
        vector<int> contribs;
        for (int i = 0; i < m; i++) {
            int b = a[i][n] - a[i][j];
            if (b > 0) contribs.push_back(b);
        }
        sort(contribs.begin(), contribs.end(), greater<int>());
        int need = total[j];
        int cnt = 0;
        for (int c : contribs) {
            need -= c;
            cnt++;
            if (need <= 0) break;
        }
        h = min(h, cnt);
    }
    return h;
}

bool dfs(int idx, int depth, int max_depth) {
    if (check()) return true;
    if (depth >= max_depth) return false;
    if (depth + heuristic() > max_depth) return false;
    
    for (int i = idx; i < m; i++) {
        cur_stations[cur_cnt++] = i + 1;
        for (int j = 1; j < n; j++) {
            total[j] -= (a[i][n] - a[i][j]);
        }
        if (dfs(i + 1, depth + 1, max_depth)) return true;
        for (int j = 1; j < n; j++) {
            total[j] += (a[i][n] - a[i][j]);
        }
        cur_cnt--;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int j = 1; j < n; j++) {
        total[j] = 0;
        for (int i = 0; i < m; i++) {
            total[j] += a[i][n] - a[i][j];
        }
    }
    
    if (check()) {
        cout << "0\n";
        return 0;
    }
    
    for (ans = 1; ans <= m; ans++) {
        cur_cnt = 0;
        if (dfs(0, 0, ans)) {
            cout << ans << "\n";
            for (int i = 0; i < ans; i++) {
                if (i > 0) cout << " ";
                cout << cur_stations[i];
            }
            cout << "\n";
            return 0;
        }
    }
    
    return 0;
}
