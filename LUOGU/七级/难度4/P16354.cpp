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

        string a, b, c;
        cin >> a >> b >> c;

        vector<int> result(n, 0);
        int cur = 1;

        for (int i = 0; i < n; i++) {
            if (a[i] == '1') {
                result[i] = cur++;
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            if (b[i] == '1' && result[i] == 0) {
                result[i] = cur++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (result[i] == 0) {
                result[i] = cur++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (i) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}
