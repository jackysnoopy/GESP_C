#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> ones(m, 0);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') ones[j]++;
        }
    }
    int ans = 0;
    for (int j = 0; j < m; j++) {
        ans = max(ans, max(ones[j], n - ones[j]));
    }
    cout << ans << "\n";
    return 0;
}
