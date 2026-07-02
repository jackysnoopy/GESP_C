#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 200005;

int p[MAXN]; // Manacher radius array

void manacher(const string& s, int* p) {
    int n = s.size();
    for (int i = 0; i < n; i++) p[i] = 0;
    int c = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (i < r) {
            p[i] = min(p[2 * c - i], r - i);
        }
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n &&
               s[i - p[i] - 1] == s[i + p[i] + 1]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s0;
    cin >> s0;
    int n = s0.size();
    
    int k;
    cin >> k;
    
    long long A, B, C, D, E;
    cin >> A >> B >> C >> D >> E;
    
    int q;
    cin >> q;
    
    // Build transformed string for Manacher: #a#b#c#...
    string t(2 * n + 1, '#');
    for (int i = 0; i < n; i++) {
        t[2 * i + 1] = s0[i];
    }
    
    manacher(t, p);
    
    // Build palindrome lookup table using sparse table
    // isPal[l][r] = true if s0[l..r] is palindrome (0-indexed)
    // Using Manacher results: substring s0[l..r] is palindrome iff
    // p[2*l + 1 + (r - l)] >= (r - l + 1) in transformed string
    
    // For efficiency with q up to 1e5, precompute prefix sums
    // isPal[l][r] can be checked via Manacher: center at 2*l+r-l+1 = l+r+1
    // radius >= r-l means the palindrome covers the substring
    
    // Process queries
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--; // convert to 0-indexed
        
        int len = r - l + 1;
        
        // Check if s0[l..r] is palindrome using Manacher
        int center = l + r + 1; // center in transformed string
        bool isPal = (p[center] >= len);
        
        if (isPal) {
            // T is palindromic substring of S0
            // Use 光归 (cost A) or 光隐 (cost C), take minimum
            cout << min(A, C) << "\n";
        } else {
            // T is not palindromic
            // Need 光隐 + 光弋: cost C + E
            // 光弋 can be used after 光隐
            cout << C + E << "\n";
        }
    }
    
    return 0;
}
