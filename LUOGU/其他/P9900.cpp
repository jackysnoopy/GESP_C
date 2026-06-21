#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> c1(n), c2(n);
    for (int i = 0; i < n; ++i) cin >> c1[i] >> c2[i];
    int a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        if (c1[i] == 0 && c2[i] == 0) ++a;
        else if (c1[i] == 1 && c2[i] == 1) ++b;
    }
    int mixed = n - a - b;
    int ans = mixed + (a + 1) / 2 + (b + 1) / 2;
    cout << ans << '\n';
    return 0;
}
