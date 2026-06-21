#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long c;
        cin >> n >> c;
        map<int,int> cnt;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        long long ans = 0;
        for (auto& p : cnt) {
            ans += min((long long)p.second, c);
        }
        cout << ans << "\n";
    }
    return 0;
}
