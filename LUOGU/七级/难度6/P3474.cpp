#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll k;
    int n;
    cin >> k >> n;
    vector<vector<ll>> a(n + 1, vector<ll>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int l = 0;
            for (int r = 1; r <= n; r++) {
                while (l < r) {
                    ll sum = a[j][r] - a[j][l] - a[i-1][r] + a[i-1][l];
                    if (sum > 2 * k) l++;
                    else break;
                }
                ll sum = a[j][r] - a[j][l] - a[i-1][r] + a[i-1][l];
                if (sum >= k && sum <= 2 * k) {
                    cout << i << " " << l + 1 << " " << j << " " << r << endl;
                    return 0;
                }
            }
        }
    }
    cout << "NIE" << endl;
    return 0;
}