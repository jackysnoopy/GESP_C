#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        int n; string s;
        cin >> n >> s;
        
        vector<int> nxt(n+1, 0);
        for (int i = 2, j = 0; i <= n; i++) {
            while (j && s[i-1] != s[j]) j = nxt[j];
            if (s[i-1] == s[j]) j++;
            nxt[i] = j;
        }
        
        cout << "Test case #" << cas << "\n";
        for (int i = 2; i <= n; i++) {
            int p = i - nxt[i];
            if (i % p == 0 && i / p > 1)
                cout << i << " " << i / p << "\n";
        }
        cout << "\n";
    }
    return 0;
}