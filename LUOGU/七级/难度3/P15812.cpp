#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> manju(n), boxes(m);
    for (int i = 0; i < n; i++) cin >> manju[i];
    for (int i = 0; i < m; i++) cin >> boxes[i];

    sort(manju.rbegin(), manju.rend());
    sort(boxes.rbegin(), boxes.rend());

    long long ans = 0;
    for (int i = 0; i < min(n, m); i++) {
        ans += min(manju[i], boxes[i]);
    }

    cout << ans << "\n";
    return 0;
}
