#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> chips(n);
    for (int i = 0; i < n; i++) cin >> chips[i];

    sort(chips.begin(), chips.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (chips[i] >= i + 1) ans++;
    }

    cout << ans << "\n";
    return 0;
}
