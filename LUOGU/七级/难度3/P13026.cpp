#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool bigger(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() > b.size();
    return a > b;
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;
        vector<string> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        long long ans = 0;
        for (int i = 1; i < n; i++) {
            if (bigger(a[i], a[i-1])) continue;
            int la = a[i].size(), lb = a[i-1].size();
            if (la == lb) {
                a[i] += '0'; ans++;
            } else {
                int diff = lb - la;
                string prefix = a[i-1].substr(0, la);
                if (a[i] == prefix) {
                    string rest = a[i-1].substr(la);
                    bool all9 = true;
                    for (char c : rest) if (c != '9') { all9 = false; break; }
                    if (all9) {
                        a[i] += string(diff + 1, '0');
                        ans += diff + 1;
                    } else {
                        string nr = rest;
                        for (int k = nr.size() - 1; k >= 0; k--) {
                            if (nr[k] < '9') { nr[k]++; break; }
                            nr[k] = '0';
                        }
                        a[i] += nr;
                        ans += diff;
                    }
                } else if (a[i] > prefix) {
                    a[i] += string(diff, '0');
                    ans += diff;
                } else {
                    a[i] += string(diff + 1, '0');
                    ans += diff + 1;
                }
            }
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
