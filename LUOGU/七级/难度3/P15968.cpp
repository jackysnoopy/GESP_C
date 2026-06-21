#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> floors(n);
    for (int i = 0; i < n; i++) cin >> floors[i];

    int ans = 0;
    for (int i = 1; i < n; i++) {
        ans += max(0, floors[i] - floors[i-1]);
    }

    cout << ans << "\n";
    return 0;
}
