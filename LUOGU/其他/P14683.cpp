#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    // Decompose and Concatenate: without full problem, implement basic approach.
    // Likely: find pattern in string decomposition.
    // Common: find longest prefix that is also suffix, or similar.
    
    // Simple approach: count unique characters
    vector<bool> seen(26, false);
    int cnt = 0;
    for (char c : s) {
        if (!seen[c - 'a']) { seen[c - 'a'] = true; cnt++; }
    }
    cout << cnt << endl;
    return 0;
}
