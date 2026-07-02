#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    long long ans = LLONG_MAX;

    for (int start = 0; start < n; start++) {
        long long cost = 0;
        int pos = 0;
        for (int i = 0; i < n; i++) {
            int idx = (start + i) % n;
            for (int j = 0; j < c[idx]; j++) {
                int d = (pos - i + n) % n;
                cost += (long long)d * d;
                pos++;
            }
        }
        ans = min(ans, cost);
    }

    cout << ans << "\n";
    return 0;
}
