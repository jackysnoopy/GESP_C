#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    sort(w.begin(), w.end(), greater<int>());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (w[i] >= ans) ans++;
    }
    cout << ans << "\n";
    return 0;
}
