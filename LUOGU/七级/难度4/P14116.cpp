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

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> fixed_pos;
        for (int i = 0; i < n; i++) {
            if (a[i] != 0) fixed_pos.push_back(i);
        }

        int unfixed = n - fixed_pos.size();
        int cycles = 0;
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++) {
            if (a[i] != 0 && !visited[i]) {
                int cur = i;
                while (!visited[cur]) {
                    visited[cur] = true;
                    cur = a[cur] - 1;
                }
                cycles++;
            }
        }

        int ans = min(n, cycles + unfixed);
        cout << ans << "\n";
    }

    return 0;
}
