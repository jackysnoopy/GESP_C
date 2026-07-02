#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];
    int loops = 0;
    for (int i = 1; i <= n; i++) if (s[i] == i) loops++;
    int min_dead = loops;
    int max_dead = 0;
    vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (vis[i] || s[i] == i) continue;
        int u = i, len = 0;
        while (!vis[u]) { vis[u] = true; u = s[u]; len++; }
        if (len == 2) { min_dead++; max_dead++; }
        else { min_dead++; max_dead += len; }
    }
    cout << min_dead << " " << max_dead << endl;
    return 0;
}