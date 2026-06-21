#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<char> dir(n);
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> dir[i] >> x[i] >> y[i];
    }
    vector<int> blocker(n, -1);
    vector<bool> alive(n, true);
    struct Event {
        long long time;
        int eid, nid;
    };
    vector<Event> events;
    for (int i = 0; i < n; i++) {
        if (dir[i] != 'E') continue;
        for (int j = 0; j < n; j++) {
            if (dir[j] != 'N') continue;
            if (x[j] > x[i] && y[i] > y[j]) {
                long long tE = x[j] - x[i];
                long long tN = y[i] - y[j];
                if (tE != tN) {
                    events.push_back({max(tE, tN), i, j});
                }
            }
        }
    }
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.time < b.time;
    });
    for (auto& ev : events) {
        int ei = ev.eid, ni = ev.nid;
        if (!alive[ei] || !alive[ni]) continue;
        long long tE = x[ni] - x[ei];
        long long tN = y[ei] - y[ni];
        if (tE < tN) {
            alive[ni] = false;
            blocker[ni] = ei;
        } else {
            alive[ei] = false;
            blocker[ei] = ni;
        }
    }
    vector<vector<int>> rev(n);
    for (int i = 0; i < n; i++) {
        if (blocker[i] >= 0) rev[blocker[i]].push_back(i);
    }
    vector<int> blame(n, 0);
    function<int(int, vector<bool>&)> dfs = [&](int u, vector<bool>& vis) -> int {
        int cnt = 0;
        for (int v : rev[u]) {
            if (!vis[v]) {
                vis[v] = true;
                cnt += 1 + dfs(v, vis);
            }
        }
        return cnt;
    };
    for (int i = 0; i < n; i++) {
        vector<bool> vis(n, false);
        vis[i] = true;
        blame[i] = dfs(i, vis);
    }
    for (int i = 0; i < n; i++) cout << blame[i] << "\n";
    return 0;
}
