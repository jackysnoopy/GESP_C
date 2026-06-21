#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> pieces(n);
    for (int i = 0; i < n; i++) cin >> pieces[i].first >> pieces[i].second;

    map<int, int> diag1, diag2;
    for (auto& [x, y] : pieces) {
        diag1[x + y]++;
        diag2[x - y]++;
    }

    int ans = 0;
    for (auto& [k, v] : diag1) ans = max(ans, v);
    for (auto& [k, v] : diag2) ans = max(ans, v);

    cout << ans << "\n";
    return 0;
}
