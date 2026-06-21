#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<long long> l(n);
        for (int i = 0; i < n; i++) cin >> l[i];
        sort(l.begin(), l.end(), greater<long long>());
        long long sum = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            sum += l[i];
            cnt++;
            if (cnt >= 3 && l[i] <= sum - l[i]) {
                break;
            }
        }
        if (cnt < 3 || l[cnt - 1] > sum - l[cnt - 1]) {
            cout << 0 << "\n";
        } else {
            cout << sum << "\n";
        }
    }
    return 0;
}
