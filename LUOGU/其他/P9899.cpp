#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> top(n), bot(n);
    for (int i = 0; i < n; ++i) cin >> top[i];
    for (int i = 0; i < n; ++i) cin >> bot[i];
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (top[i] == bot[i]) ++ans;
        else ans += 2;
    }
    cout << ans << '\n';
    return 0;
}
