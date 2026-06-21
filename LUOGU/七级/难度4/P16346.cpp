#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long sum = 0;
        for (int i = 0; i < n; i++) sum += a[i];

        if (sum % n != 0) {
            cout << "No\n";
            continue;
        }

        long long target = sum / n;
        long long diff = 0;
        bool possible = true;

        for (int i = 0; i < n; i++) {
            diff += a[i] - target;
            if (diff < 0) {
                possible = false;
                break;
            }
        }

        cout << (possible ? "Yes" : "No") << "\n";
    }

    return 0;
}
