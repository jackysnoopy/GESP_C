#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    // Last day: 1st gets n pts, 2nd gets n-1, ..., last gets 1.
    // A player can be champion if their total (current + last day pts) >= max possible total.
    // Max possible for player i = b[i] + n (if they get 1st place last day).
    // A player can be champion iff b[i] + n >= b[j] + 1 for all j.
    // i.e., b[i] + n >= max(b) + 1 iff b[i] >= max(b) + 1 - n.
    int mx = *max_element(b.begin(), b.end());
    int threshold = mx + 1 - n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] >= threshold) ans++;
    }
    cout << ans << "\n";
    return 0;
}
