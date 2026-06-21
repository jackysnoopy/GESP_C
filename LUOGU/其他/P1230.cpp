#include <iostream>
#include <algorithm>
using namespace std;
struct Task { int t, w; };
bool cmp(const Task& a, const Task& b) { return a.w > b.w; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    Task tasks[501];
    for (int i = 0; i < n; i++) cin >> tasks[i].t;
    for (int i = 0; i < n; i++) cin >> tasks[i].w;
    sort(tasks, tasks + n, cmp);
    bool used[501] = {};
    for (int i = 0; i < n; i++) {
        int slot = tasks[i].t;
        while (slot > 0 && used[slot]) slot--;
        if (slot > 0) { used[slot] = true; m -= 0; }
        else m -= tasks[i].w;
    }
    cout << m << "\n";
    return 0;
}
