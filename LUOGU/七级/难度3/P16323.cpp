#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;
    int cur = 0;
    for (int x : a) {
        cur = max(x, cur + x);
        ans = max(ans, cur);
    }

    cout << ans << "\n";
    return 0;
}
