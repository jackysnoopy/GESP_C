#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Stars needed for each digit 0-9 (from the character art)
int cost[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // Build max number using at most n stars
    // Use digit 1 (cost 2) as filler, build greedily
    // To maximize number: maximize length first, then lexicographic order
    // Max length = n / 2 (all 1s)
    // Then try to replace from left with larger digits
    int len = n / 2;
    if (len == 0) { cout << 0 << "\n"; return 0; }
    string ans(len, '1');
    int rem = n - len * 2;
    for (int i = 0; i < len; i++) {
        for (int d = 9; d >= 0; d--) {
            int extra = cost[d] - 2; // extra stars needed vs digit 1
            if (extra <= rem) {
                ans[i] = '0' + d;
                rem -= extra;
                break;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
