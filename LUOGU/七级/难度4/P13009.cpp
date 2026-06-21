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
        long long m;
        cin >> n >> m;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long max_sum = 0;
        int ops = 0;

        for (int i = 0; i < n; i++) {
            long long val = a[i];
            long long transformed = m / val;
            if (transformed > val) {
                max_sum += transformed;
                ops++;
            } else {
                max_sum += val;
            }
        }

        cout << max_sum << " " << ops << "\n";
    }

    return 0;
}
