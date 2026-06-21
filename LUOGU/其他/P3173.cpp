#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> x(m-1), y(n-1);
    for (int i = 0; i < n-1; i++) cin >> y[i];
    for (int i = 0; i < m-1; i++) cin >> x[i];
    sort(y.rbegin(), y.rend());
    sort(x.rbegin(), x.rend());
    long long ans = 0;
    long long pieces_h = 1, pieces_v = 1;
    int yi = 0, xi = 0;
    while (yi < n-1 || xi < m-1) {
        if (yi < n-1 && (xi >= m-1 || y[yi] >= x[xi])) {
            ans += y[yi] * pieces_v;
            pieces_h++;
            yi++;
        } else {
            ans += x[xi] * pieces_h;
            pieces_v++;
            xi++;
        }
    }
    cout << ans << "\n";
    return 0;
}
