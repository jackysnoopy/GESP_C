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

    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) pos[a[i]] = i;

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (pos[i] != i - 1) {
            ans += abs(pos[i] - (i - 1));
        }
    }

    cout << ans << "\n";
    return 0;
}
