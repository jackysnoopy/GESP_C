#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        adj[i].push_back(a);
        adj[i].push_back(b);
    }
    vector<int> degree(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j : adj[i]) degree[j]++;
    }
    for (int i = 1; i <= n; i++) {
        if (degree[i] != 2) { cout << -1 << "\n"; return 0; }
    }
    vector<bool> visited(n + 1, false);
    vector<vector<int>> cycles;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> cycle;
            int cur = i, prev = -1;
            while (!visited[cur]) {
                visited[cur] = true;
                cycle.push_back(cur);
                for (int next : adj[cur]) {
                    if (next != prev) { prev = cur; cur = next; break; }
                }
            }
            cycles.push_back(cycle);
        }
    }
    if (cycles.size() != 1) { cout << -1 << "\n"; return 0; }
    vector<int>& cycle = cycles[0];
    int m = cycle.size();
    if (m != n) { cout << -1 << "\n"; return 0; }
    int max_correct = 0;
    for (int rot = 0; rot < m; rot++) {
        int correct = 0;
        for (int j = 0; j < m; j++) {
            int person = cycle[(j + rot) % m];
            int left = cycle[(j + rot - 1 + m) % m];
            int right = cycle[(j + rot + 1) % m];
            bool left_ok = (left == adj[person][0] || left == adj[person][1]);
            bool right_ok = (right == adj[person][0] || right == adj[person][1]);
            if (left_ok && right_ok) correct++;
        }
        max_correct = max(max_correct, correct);
    }
    cout << n - max_correct << "\n";
    return 0;
}
