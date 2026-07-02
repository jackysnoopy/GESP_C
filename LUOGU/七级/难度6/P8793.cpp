#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    long long total = 0;
    int prefix_o = 0;
    int suffix_o = 0;
    bool has_w = false;
    
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        
        int cnt = 0;
        for (int j = 0; j + 2 < s.size(); j++) {
            if (s[j] == 'o' && s[j+1] == 'w' && s[j+2] == 'o') {
                cnt++;
            }
        }
        
        total += cnt;
        
        int pref = 0;
        for (char c : s) {
            if (c == 'o') pref++;
            else break;
        }
        
        int suff = 0;
        for (int j = s.size() - 1; j >= 0; j--) {
            if (s[j] == 'o') suff++;
            else break;
        }
        
        bool has_w_in = false;
        for (char c : s) {
            if (c == 'w') {
                has_w_in = true;
                break;
            }
        }
        
        if (has_w && pref > 0) {
            total += min(prefix_o, pref);
        }
        
        if (has_w_in && suffix_o > 0) {
            total += min(suff, suffix_o);
        }
        
        if (pref == s.size()) {
            prefix_o += pref;
        } else {
            prefix_o = pref;
        }
        
        if (suff == s.size()) {
            suffix_o += suff;
        } else {
            suffix_o = suff;
        }
        
        if (has_w_in) {
            has_w = true;
        }
        
        cout << total << "\n";
    }
    
    return 0;
}