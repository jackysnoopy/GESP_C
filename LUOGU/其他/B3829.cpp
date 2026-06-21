#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    if (k == 1) {
        cout << n << "\n";
        for (int i = 0; i < n; i++) {
            cout << s[i] << "\n";
        }
        return 0;
    }
    for (int split_pos = n / k; split_pos >= 1; split_pos--) {
        if (split_pos * k < n) continue;
        vector<string> parts;
        int idx = 0;
        bool ok = true;
        string built = "";
        for (int p = 0; p < k - 1; p++) {
            string part = s.substr(idx, split_pos);
            if (p > 0) {
                if (built.find(part) == string::npos) {
                    ok = false;
                    break;
                }
            }
            parts.push_back(part);
            built += part;
            idx += split_pos;
        }
        if (!ok) continue;
        string last_part = s.substr(idx);
        if (k > 1 && built.find(last_part) == string::npos) {
            continue;
        }
        parts.push_back(last_part);
        cout << parts.size() << "\n";
        for (auto& p : parts) cout << p << "\n";
        return 0;
    }
    cout << -1 << "\n";
    return 0;
}
