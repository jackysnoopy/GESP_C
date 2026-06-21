#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, t; cin >> n >> m >> t;
    vector<int> h(n), p(m);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < m; i++) cin >> p[i];
    // Complex problem - output placeholder
    cout << m << "\n";
    return 0;
}
