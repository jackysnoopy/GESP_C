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

        vector<string> grid(n);
        for (int i = 0; i < n; i++) cin >> grid[i];

        int hash_count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '#') hash_count++;
            }
        }

        int ops = (hash_count + m - 1) / m;
        long long ways = 1;

        for (int i = 0; i < ops; i++) {
            ways = ways * 2 % 998244353;
        }

        cout << ops << " " << ways << "\n";
    }

    return 0;
}
