#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<double> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> produce(n + 1);
    vector<vector<int>> consume(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y, k, w;
        cin >> x >> y >> k >> w;
        if (k == 0) {
            produce[y].push_back(w);
        } else {
            consume[y].push_back(x);
        }
    }

    double ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) {
            ans = max(ans, a[i]);
        }
    }

    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}
