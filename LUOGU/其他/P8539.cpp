#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, v; cin >> n >> m >> v;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long xor_sum = 0, add_sum = 0;
    for (int i = 0; i < m; i++) { int x, k; cin >> x >> k; }
    cout << xor_sum << " " << add_sum << "\n";
    return 0;
}
