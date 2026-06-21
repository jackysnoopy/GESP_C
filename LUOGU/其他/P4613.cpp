#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> w(n), b(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(w.begin(), w.end());
    sort(b.begin(), b.end());
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (w[i] > b[i]) { ok = false; break; }
    }
    cout << (ok ? "DA" : "NE") << "\n";
    return 0;
}
