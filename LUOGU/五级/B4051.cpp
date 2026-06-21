#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    long long sum_pos = 0;
    for (int i = 0; i < m; i++) {
        int a; cin >> a;
        if (a > 0) sum_pos += a;
    }
    cout << *max_element(c.begin(), c.end()) + sum_pos << "\n";
    return 0;
}
