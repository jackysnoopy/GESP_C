#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> parent(n + 1), l(n + 1), r(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> parent[i] >> l[i] >> r[i];
    }

    vector<char> op(n + 1);
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> op[i] >> a[i];
    }

    while (q--) {
        long long x;
        cin >> x;

        int count = 0;
        for (int i = 1; i <= n; i++) {
            long long val = x;
            int cur = i;
            bool valid = true;

            while (cur != 1) {
                if (val < l[cur] || val > r[cur]) {
                    valid = false;
                    break;
                }
                val = (op[cur] == '+') ? val + a[cur] : val - a[cur];
                cur = parent[cur];
            }

            if (valid) count++;
        }

        cout << count << "\n";
    }

    return 0;
}
