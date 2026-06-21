#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, b;
    cin >> n >> b;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    sort(h.rbegin(), h.rend());
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += h[i];
        if (sum >= b) { cout << i + 1 << "\n"; return 0; }
    }
    return 0;
}
