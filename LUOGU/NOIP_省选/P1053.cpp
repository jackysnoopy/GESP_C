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
    vector<int> cycle;
    int cur = 1, prev = -1;
    while (!visited[cur]) {
        visited[cur] = true;
        cycle.push_back(cur);
        for (int next : adj[cur]) {
            if (next != prev) { prev = cur; cur = next; break; }
        }
    }

    if ((int)cycle.size() != n) { cout << -1 << "\n"; return 0; }

    vector<int> freq(n, 0);
    for (int j = 0; j < n; j++) {
        int k = (cycle[j] - 1 - j + n) % n;
        freq[k]++;
    }

    int maxCorrect = 0;
    for (int k = 0; k < n; k++) {
        maxCorrect = max(maxCorrect, freq[k]);
    }

    cout << n - maxCorrect << endl;
    return 0;
}
