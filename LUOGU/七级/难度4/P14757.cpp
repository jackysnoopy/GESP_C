#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        bool possible = true;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                possible = false;
                break;
            }
            if (i > 0 && a[i] - a[i - 1] != b[i] - b[i - 1]) {
                if (a[i] - a[i - 1] < b[i] - b[i - 1]) {
                    possible = false;
                    break;
                }
            }
        }

        cout << (possible ? "YES" : "NO") << "\n";
    }

    return 0;
}
