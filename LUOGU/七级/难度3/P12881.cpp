#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> scores(n);
    for (int i = 0; i < n; i++) {
        cin >> scores[i];
    }

    sort(scores.rbegin(), scores.rend());

    int ans = 0;
    for (int i = 0; i < m && i < n; i++) {
        ans += scores[i];
    }

    cout << ans << "\n";
    return 0;
}
