#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        long long d;
        cin >> n >> d;
        vector<long long> x(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        // Work backwards: latest day for last bus
        long long day = d;
        for (int i = n - 1; i >= 0; i--) {
            day = (day / x[i]) * x[i];
        }
        cout << "Case #" << t << ": " << day << "\n";
    }
    return 0;
}
