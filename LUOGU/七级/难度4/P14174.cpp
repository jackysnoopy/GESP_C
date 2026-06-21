#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> gains;
    long long total = 0;

    for (int i = 0; i < n; i++) {
        int x, l;
        cin >> x >> l;

        vector<long long> a(l), b(l);
        for (int j = 0; j < l; j++) cin >> a[j];
        for (int j = 0; j < l; j++) cin >> b[j];

        long long prod = x;
        for (int j = 0; j < l; j++) prod *= a[j];
        total += prod;

        for (int j = 0; j < l; j++) {
            if (b[j] > 0) {
                long long gain = x;
                for (int m = 0; m < l; m++) {
                    if (m == j) gain *= (a[m] - b[m]);
                    else gain *= a[m];
                }
                gains.push_back(prod - gain);
            }
        }
    }

    sort(gains.begin(), gains.end(), greater<int>());

    long long ans = total;
    for (int i = 0; i < min(k, (int)gains.size()); i++) {
        ans -= gains[i];
    }

    cout << ans << "\n";
    return 0;
}
