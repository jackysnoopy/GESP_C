#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s;
    cin >> n >> s;
    long long ans = 0;
    int prevCost = 0;
    for (int i = 0; i < n; i++) {
        int c, y;
        cin >> c >> y;
        prevCost = min(prevCost + s, c);
        ans += (long long)prevCost * y;
    }
    cout << ans << "\n";
    return 0;
}
