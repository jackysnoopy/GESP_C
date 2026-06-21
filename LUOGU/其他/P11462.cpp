#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, M;
    cin >> n >> M;
    vector<int> c(n), k(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n; i++) cin >> k[i];
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return (double)c[i] / k[i] > (double)c[j] / k[j];
    });
    double ans = 0;
    int rem = M;
    for (int i = 0; i < n && rem > 0; i++) {
        int id = idx[i];
        int use = min(rem, k[id]);
        ans += (double)use / k[id] * c[id] * 100;
        rem -= use;
    }
    cout << fixed << setprecision(4) << ans << "\n";
    return 0;
}
