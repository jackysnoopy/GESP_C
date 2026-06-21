#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> k(n), x1(n), x2(n);
    vector<vector<int>> doors(n);

    for (int i = 0; i < n; i++) {
        cin >> k[i] >> x1[i] >> x2[i];
        doors[i].resize(k[i]);
        for (int j = 0; j < k[i]; j++) {
            cin >> doors[i][j];
        }
    }

    int total_doors = 0;
    for (int i = 0; i < n; i++) {
        total_doors += k[i];
    }

    if (total_doors == 0) {
        cout << "0\n";
        return 0;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int door_sum = 0;
        for (int j = 0; j < k[i]; j++) {
            door_sum += doors[i][j];
        }
        int max_opening = x2[i] - x1[i] - door_sum;
        ans = max(ans, max_opening);
    }

    cout << ans << "\n";
    return 0;
}
