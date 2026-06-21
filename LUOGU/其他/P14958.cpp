#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> b(n);
    for (int i = 0; i < n; i++) b[i] = i + 1;
    for (int iter = 0; iter < 100; iter++) {
        vector<long long> p(n);
        for (int i = 0; i < n; i++) p[i] = a[i] * (long long)b[i];
        bool ok = true;
        for (int i = 0; i + 1 < n; i++) {
            if (p[i] == p[i + 1]) { ok = false; break; }
        }
        if (ok) break;
        for (int i = 0; i + 1 < n; i++) {
            if (p[i] == p[i + 1]) { swap(b[i], b[i + 1]); break; }
        }
    }
    vector<long long> p(n);
    for (int i = 0; i < n; i++) p[i] = a[i] * (long long)b[i];
    for (int i = 0; i + 1 < n; i++) {
        if (p[i] == p[i + 1]) { cout << -1 << "\n"; return 0; }
    }
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << b[i];
    }
    cout << "\n";
    return 0;
}
