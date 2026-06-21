#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    vector<int> kp;
    vector<char> kc;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'F') { kp.push_back(i); kc.push_back(s[i]); }
    }
    
    if (kp.empty()) {
        cout << n << "\n";
        for (int i = 0; i < n; i++) { if (i) cout << "\n"; cout << i; }
        cout << "\n";
        return 0;
    }
    
    long long min_exc = 0, max_exc = 0;
    int step = 1; // overall step size (gcd)
    
    // Leading F's
    int lead = kp[0];
    max_exc += lead;
    
    // Trailing F's
    int trail = n - 1 - kp.back();
    max_exc += trail;
    
    // Middle segments
    for (int i = 0; i + 1 < (int)kp.size(); i++) {
        int sl = kp[i+1] - kp[i] - 1;
        if (sl == 0) {
            if (kc[i] == kc[i+1]) { min_exc += 1; max_exc += 1; }
        } else if (kc[i] == kc[i+1]) {
            max_exc += sl + 1;
            if (sl == 1) step = 2;
        } else {
            if (sl % 2 == 1) min_exc += 1;
            max_exc += sl;
            if (sl <= 2) step = 2;
        }
    }
    
    if (lead > 0 || trail > 0) step = 1;
    
    vector<long long> res;
    for (long long v = min_exc; v <= max_exc; v += step) res.push_back(v);
    
    cout << res.size() << "\n";
    for (int i = 0; i < (int)res.size(); i++) { if (i) cout << "\n"; cout << res[i]; }
    cout << "\n";
    return 0;
}
