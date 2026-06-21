#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w, k;
    cin >> h >> w >> k;

    vector<int> c(k);
    for (int i = 0; i < k; i++) cin >> c[i];

    if (k > h * w) {
        cout << "-1\n";
        return 0;
    }

    sort(c.begin(), c.end());

    int ans = 0;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int dist = abs(c[i] - c[j]);
            ans = max(ans, dist);
        }
    }

    cout << ans << "\n";
    return 0;
}
