#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b;
    cin >> a >> b;
    long long total = a + b;
    long long n = (long long)((sqrt(8.0 * total + 1) - 1) / 2);
    if (n * (n + 1) / 2 != total) { cout << "No\n"; return 0; }
    long long target = min(a, b);
    vector<int> res;
    for (int i = (int)n; i >= 1; i--) {
        if (target >= i) { res.push_back(i); target -= i; }
    }
    if (target != 0) { cout << "No\n"; return 0; }
    cout << n;
    for (int i = (int)res.size() - 1; i >= 0; i--) cout << " " << res[i];
    cout << "\n";
    return 0;
}
