#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string p, q;
        cin >> p >> q;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (p[i] == '1') cnt++;
            if (q[i] == '1') cnt++;
        }
        if (cnt % 2 != 0) {
            cout << "++\n";
            continue;
        }
        int ones1 = 0, ones2 = 0;
        for (int i = 0; i < n; i++) {
            if (p[i] == '1') ones1++;
            if (q[i] == '1') ones2++;
        }
        if (ones1 == 0 && ones2 == 0) {
            cout << "RP\n";
            continue;
        }
        if (ones1 % 2 == 0 && ones2 % 2 == 0) {
            cout << "RP\n";
        } else if (ones1 % 2 == 1 && ones2 % 2 == 1) {
            cout << "RP\n";
        } else {
            cout << "++\n";
        }
    }
    return 0;
}
