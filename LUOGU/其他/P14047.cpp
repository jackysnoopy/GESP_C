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
        vector<long long> a(n);
        long long total = 0;
        for (int i = 0; i < n; i++) { cin >> a[i]; total += a[i]; }
        long long avg = total / n;
        long long excess = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > avg) excess += a[i] - avg;
        }
        cout << excess << "\n";
    }
    return 0;
}
