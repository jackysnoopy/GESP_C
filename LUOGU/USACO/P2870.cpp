#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s(n, ' ');
    for (int i = 0; i < n; i++) cin >> s[i];
    int l = 0, r = n-1, cnt = 0;
    string res = "";
    while (l <= r) {
        if (s[l] < s[r]) { res += s[l++]; }
        else if (s[l] > s[r]) { res += s[r--]; }
        else {
            int ll = l, rr = r;
            while (ll <= rr && s[ll] == s[rr]) { ll++; rr--; }
            if (ll > rr || s[ll] < s[rr]) res += s[l++];
            else res += s[r--];
        }
        cnt++;
        if (cnt % 80 == 0) res += "\n";
    }
    cout << res << "\n";
    return 0;
}
