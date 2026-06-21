#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        string A;
        cin >> n >> m >> A;
        if (n == 1 && m == 1) {
            cout << "-1\n";
            continue;
        }
        string B = "";
        for (int i = 0; i < m; i++) {
            B += (i % 2 == 0) ? "0" : "1";
        }
        cout << B << "\n";
    }
    return 0;
}
