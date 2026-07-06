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
    long long sum_pos = 0, sum_all = 0;
    for (int i = 0; i < m; i++) {
        int a; cin >> a;
        sum_all += a;
        if (a > 0) sum_pos += a;
    }
    long long mx = *max_element(c.begin(), c.end());
    if (n == 1) cout << mx + sum_all << "\n";
    else cout << mx + sum_pos << "\n";
    return 0;
}
