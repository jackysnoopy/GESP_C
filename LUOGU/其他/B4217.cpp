#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    vector<long long> res = h;
    for (int i = 0; i < n; i++) {
        if (h[i] != 0) {
            if (i > 0 && h[i-1] != 0 && h[i-1] >= h[i]) {
                cout << "NO\n"; return 0;
            }
            if (i < n-1 && h[i+1] != 0 && h[i+1] <= h[i]) {
                cout << "NO\n"; return 0;
            }
        }
    }
    long long last = 0;
    for (int i = 0; i < n; i++) {
        if (h[i] != 0) {
            long long min_needed = last + 1;
            if (h[i] < min_needed) {
                cout << "NO\n"; return 0;
            }
            last = h[i];
        } else {
            last++;
        }
    }
    long long last_val = 0;
    for (int i = 0; i < n; i++) {
        if (h[i] != 0) {
            res[i] = h[i];
            last_val = h[i];
        } else {
            long long lo = last_val + 1;
            if (lo > 1000000000LL) { cout << "NO\n"; return 0; }
            res[i] = lo;
            last_val = lo;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << res[i];
    }
    cout << "\n";
    return 0;
}
