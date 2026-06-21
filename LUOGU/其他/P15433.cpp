#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<bool> lit(n + 2, false);
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int a; cin >> a;
        if (!lit[a - 1] && !lit[a + 1] && !lit[a]) {
            lit[a] = true;
            cnt++;
        }
    }
    cout << cnt << "\n";
    return 0;
}
