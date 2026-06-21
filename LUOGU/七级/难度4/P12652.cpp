#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; i++) cin >> parent[i];

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++) children[parent[i]].push_back(i);

    vector<int> result;
    int root = 1;

    while (n > 0) {
        result.push_back(a[root]);

        int cur = root;
        while (!children[cur].empty()) {
            int next = -1;
            for (int c : children[cur]) {
                if (next == -1 || a[c] < a[next]) next = c;
            }
            swap(a[cur], a[next]);
            cur = next;
        }

        int p = parent[cur];
        if (p != 0) {
            auto it = find(children[p].begin(), children[p].end(), cur);
            children[p].erase(it);
        }

        n--;
        if (n > 0) root = 1;
    }

    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << "\n";
    }

    return 0;
}
