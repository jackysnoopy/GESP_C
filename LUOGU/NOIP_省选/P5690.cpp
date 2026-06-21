#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int m1 = s[0] - '0', m2 = s[1] - '0';
    int d1 = s[3] - '0', d2 = s[4] - '0';
    int ans = 4;
    for (int mo = 1; mo <= 12; mo++) {
        for (int d = 1; d <= days[mo]; d++) {
            int cm1 = mo / 10, cm2 = mo % 10;
            int cd1 = d / 10, cd2 = d % 10;
            int diff = 0;
            if (cm1 != m1) diff++;
            if (cm2 != m2) diff++;
            if (cd1 != d1) diff++;
            if (cd2 != d2) diff++;
            ans = min(ans, diff);
        }
    }
    cout << ans << "\n";
    return 0;
}
