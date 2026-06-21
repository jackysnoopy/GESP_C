#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        int K;
        string s;
        cin >> K >> s;
        long long ans = 0;
        for (char c : s) {
            int val;
            if (c >= '0' && c <= '9') val = c - '0';
            else val = c - 'A' + 10;
            ans = ans * K + val;
        }
        cout << ans << "\n";
    }
    return 0;
}
