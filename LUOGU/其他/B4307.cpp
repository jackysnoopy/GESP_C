#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        int cnt[2][2] = {{0,0},{0,0}};
        for (int i = 0; i < n; i++) cnt[a[i]][b[i]]++;
        int diff01 = cnt[0][1];
        int diff10 = cnt[1][0];
        if (diff01 == 0 && diff10 == 0) {
            cout << 0 << "\n";
        } else if (diff01 == 0 || diff10 == 0) {
            cout << -1 << "\n";
        } else {
            cout << max(diff01, diff10) << "\n";
        }
    }
    return 0;
}
