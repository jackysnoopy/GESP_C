#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> votes(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> votes[i][j];
        }
    }

    vector<int> total(n, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            total[j] += votes[i][j];
        }
    }

    int opp = total[n - 1];
    int max_other = *max_element(total.begin(), total.end() - 1);

    if (opp <= max_other) {
        cout << "0\n";
        return 0;
    }

    vector<int> order(m);
    for (int i = 0; i < m; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return votes[x][n - 1] > votes[y][n - 1];
    });

    vector<int> canceled;
    for (int i : order) {
        canceled.push_back(i + 1);
        total[n - 1] -= votes[i][n - 1];
        for (int j = 0; j < n - 1; j++) {
            total[j] -= votes[i][j];
        }
        opp = total[n - 1];
        max_other = *max_element(total.begin(), total.end() - 1);
        if (opp <= max_other) break;
    }

    cout << canceled.size() << "\n";
    for (int i = 0; i < (int)canceled.size(); i++) {
        if (i) cout << " ";
        cout << canceled[i];
    }
    cout << "\n";

    return 0;
}
