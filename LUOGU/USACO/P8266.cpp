#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    // Count GG pairs at (odd, even) positions (1-indexed)
    // which is (even, odd) in 0-indexed: positions (0,1), (2,3), (4,5), ...
    int cnt = 0;
    for (int i = 0; i < n - 1; i += 2) {
        if (s[i] == 'G' && s[i + 1] == 'G') cnt++;
    }
    cout << cnt << "\n";
    return 0;
}
