#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n + 1, false);
        int components = 0;

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                components++;
                vector<int> stack;
                stack.push_back(i);
                visited[i] = true;

                while (!stack.empty()) {
                    int u = stack.back();
                    stack.pop_back();
                    for (int v : adj[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            stack.push_back(v);
                        }
                    }
                }
            }
        }

        cout << components - 1 << "\n";
    }

    return 0;
}
