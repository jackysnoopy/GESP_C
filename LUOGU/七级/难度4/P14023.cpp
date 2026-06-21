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
        int n, m, k;
        cin >> n >> m >> k;

        vector<bool> is_friend(k + 1, false);
        for (int i = 0; i < n; i++) {
            int f;
            cin >> f;
            is_friend[f] = true;
        }

        vector<pair<int, int>> comments(m);
        for (int i = 0; i < m; i++) {
            cin >> comments[i].first >> comments[i].second;
        }

        int visible = 0;
        for (auto& [a, b] : comments) {
            if (is_friend[a] && is_friend[b]) visible++;
        }

        cout << visible << "\n";
    }

    return 0;
}
