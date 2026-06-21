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
        vector<pair<int, int>> mach(n), ord(n);
        for (int i = 0; i < n; i++) {
            cin >> mach[i].first;
            mach[i].second = i + 1;
        }
        for (int i = 0; i < n; i++) {
            cin >> ord[i].first;
            ord[i].second = i + 1;
        }
        sort(mach.rbegin(), mach.rend());
        sort(ord.rbegin(), ord.rend());
        long long sum_prod = 0, sum_order = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            sum_prod += mach[i].first;
            sum_order += ord[i].first;
            if (sum_prod < sum_order) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for (int i = 0; i < n; i++) cout << mach[i].second << " \n"[i == n - 1];
            for (int i = 0; i < n; i++) cout << ord[i].second << " \n"[i == n - 1];
        }
    }
    return 0;
}
