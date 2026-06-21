#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> ans(n + 1, 0);
    vector<int> cur(n + 1);
    for (int i = 1; i <= n; i++) cur[i] = i - 1;
    for (int i = 0; i < m; i++) {
        int p;
        cin >> p;
        for (int j = 1; j <= n; j++) {
            int val = abs(j - p);
            cur[j] = val;
            if (val > ans[j]) ans[j] = val;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
