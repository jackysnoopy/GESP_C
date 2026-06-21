#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string A;
        cin >> A;
        // Perfect palindrome: for ALL rotations, the string is a palindrome.
        // A string is perfect palindrome iff all characters are the same, or n <= 1.
        // Actually: for a string to be a palindrome for all rotations:
        // f(S,0) = S is palindrome → s[i] = s[n-1-i]
        // f(S,1) = s[1]..s[n-1]s[0] is palindrome → s[1]=s[0], s[2]=s[n-1], etc.
        // This implies all characters must be the same.
        // Wait, let me check: "aa" → rotations: "aa" (palindrome). Yes.
        // "aba" → rotations: "aba" (palindrome), "baa" (not palindrome). No.
        // "abba" → rotations: "abba" (palindrome), "bbaa" (not). No.
        // So only strings with all same chars work.
        // Minimum changes = n - max frequency of any character.
        
        int cnt[26] = {};
        for (char c : A) cnt[c - 'a']++;
        int mx = 0;
        for (int i = 0; i < 26; i++) mx = max(mx, cnt[i]);
        cout << n - mx << "\n";
    }
    return 0;
}
