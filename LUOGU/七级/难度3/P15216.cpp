#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i <= n - k; i++) {
        bool ok = true;
        for (int j = 1; j < k; j++) {
            if (a[i+j] != a[i] + j) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << i + 1 << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
