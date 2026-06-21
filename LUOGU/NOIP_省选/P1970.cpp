#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    if (n <= 2) { cout << n << "\n"; return 0; }
    int ans = 1;
    int prev_dir = 0;
    for (int i = 1; i < n; i++) {
        int d = (h[i] > h[i-1]) ? 1 : (h[i] < h[i-1]) ? -1 : 0;
        if (d != 0 && d != prev_dir) {
            ans++;
            prev_dir = d;
        } else if (d != 0) {
            // extend trend
        }
    }
    cout << ans << "\n";
    return 0;
}
