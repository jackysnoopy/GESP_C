#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> eert(int N, vector<int> f) {
    if (N <= 1) return vector<int>();

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; i++) {
        adj[i + 2].push_back(f[i]);
        adj[f[i]].push_back(i + 2);
    }

    vector<int> degree(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        degree[i] = adj[i].size();
    }

    vector<int> result;
    vector<bool> used(N + 1, false);

    for (int i = 1; i <= N; i++) {
        if (!used[i]) {
            result.push_back(i);
            used[i] = true;
        }
    }

    if (result.size() != N) return vector<int>();

    bool valid = true;
    for (int i = 1; i < N; i++) {
        bool connected = false;
        for (int v : adj[result[i - 1]]) {
            if (v == result[i]) {
                connected = true;
                break;
            }
        }
        if (connected) {
            valid = false;
            break;
        }
    }

    if (!valid) return vector<int>();
    return result;
}

int main() {
    int N;
    cin >> N;

    vector<int> f(N - 1);
    for (int i = 0; i < N - 1; i++) cin >> f[i];

    vector<int> result = eert(N, f);

    if (result.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int i = 0; i < N; i++) {
            if (i) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}
