#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, q;
    cin >> n >> k >> q;

    vector<int> p(q), l(q), r(q);
    for (int i = 0; i < q; i++) cin >> p[i] >> l[i] >> r[i];

    vector<int> result(q, 0);
    int keys_available = k;

    for (int i = 0; i < q; i++) {
        if (keys_available > 0) {
            result[i] = 1;
            keys_available--;
        } else {
            result[i] = 0;
        }
        keys_available++;
        if (keys_available > k) keys_available = k;
    }

    for (int i = 0; i < q; i++) cout << result[i];
    cout << "\n";

    return 0;
}
