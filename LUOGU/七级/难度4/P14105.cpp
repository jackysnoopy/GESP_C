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
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> tails;
        vector<int> pos(n, -1);

        for (int i = 0; i < n; i++) {
            auto it = upper_bound(tails.begin(), tails.end(), a[i]);
            int idx = it - tails.begin();
            if (it == tails.end()) {
                tails.push_back(a[i]);
            } else {
                *it = a[i];
            }
            pos[i] = idx;
        }

        int m = tails.size();
        cout << m << "\n";

        vector<vector<int>> subsequences(m);
        for (int i = n - 1; i >= 0; i--) {
            subsequences[pos[i]].push_back(i + 1);
        }

        for (int i = 0; i < m; i++) {
            sort(subsequences[i].begin(), subsequences[i].end());
            cout << subsequences[i].size();
            for (int x : subsequences[i]) cout << " " << x;
            cout << "\n";
        }
    }

    return 0;
}
