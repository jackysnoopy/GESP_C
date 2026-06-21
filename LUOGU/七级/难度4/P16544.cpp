#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long total = 0;
    for (int i = 0; i < n; i++) total += a[i];

    long long max_a = *max_element(a.begin(), a.end());

    while (q--) {
        long long k;
        cin >> k;

        if (k == 1) {
            cout << "YES\n";
        } else if (k > total) {
            cout << "NO\n";
        } else if (k > max_a) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
