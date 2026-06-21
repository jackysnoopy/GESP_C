#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int min_val = *min_element(a.begin(), a.end());
    int max_val = *max_element(a.begin(), a.end());

    int ans = max_val - min_val;

    for (int diff = 0; diff <= ans; diff++) {
        int ops = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > min_val + diff) ops++;
        }
        if (ops <= m) {
            ans = diff;
            break;
        }
    }

    cout << ans << "\n";
    return 0;
}
