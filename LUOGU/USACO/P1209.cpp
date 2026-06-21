#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, s, c;
    cin >> m >> s >> c;
    vector<int> pos(c);
    for (int i = 0; i < c; i++) cin >> pos[i];
    sort(pos.begin(), pos.end());
    if (m >= c) {
        cout << c << "\n";
        return 0;
    }
    vector<int> gap(c - 1);
    for (int i = 0; i < c - 1; i++) gap[i] = pos[i + 1] - pos[i] - 1;
    sort(gap.begin(), gap.end(), greater<int>());
    int total = pos[c - 1] - pos[0] + 1;
    for (int i = 0; i < m - 1 && i < (int)gap.size(); i++) {
        total -= gap[i];
    }
    cout << total << "\n";
    return 0;
}
