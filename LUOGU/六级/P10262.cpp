#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    string s;
    cin >> p >> s;

    vector<long long> cnt(p, 0);
    long long ans = 0;

    for (char ch : s) {
        int d = ch - '0';
        vector<long long> new_cnt(p, 0);
        new_cnt[d % p]++;

        for (int r = 0; r < p; r++) {
            if (cnt[r] == 0) continue;
            int nr = (r * 10 + d) % p;
            new_cnt[nr] += cnt[r];
        }

        ans += new_cnt[0];
        cnt.swap(new_cnt);
    }

    cout << ans << "\n";
    return 0;
}
