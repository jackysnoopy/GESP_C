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
    // Without full problem, implement basic approach.
    // Likely: maximize something with card game.
    sort(a.rbegin(), a.rend());
    long long ans = 0;
    for (int i = 0; i < n; i += 2) ans += a[i];
    cout << ans << endl;
    return 0;
}
