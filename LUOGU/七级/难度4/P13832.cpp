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

        string A, B;
        cin >> A >> B;

        vector<int> c(n);
        for (int i = 0; i < n; i++) cin >> c[i];

        long long ans = 0;
        bool possible = true;

        for (int i = 0; i < n; i++) {
            if (A[i] == '0' && B[i] == '1') {
                ans += c[n - 1 - i];
            } else if (A[i] == '1' && B[i] == '0') {
                possible = false;
                break;
            }
        }

        cout << (possible ? to_string(ans) : "-1") << "\n";
    }

    return 0;
}
