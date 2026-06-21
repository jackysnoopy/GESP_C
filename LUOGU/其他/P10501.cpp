#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int w, h;
        cin >> w >> h;
        if (((w - 1) ^ (h - 1)) != 0)
            cout << "WIN" << '\n';
        else
            cout << "LOSE" << '\n';
    }
    return 0;
}
