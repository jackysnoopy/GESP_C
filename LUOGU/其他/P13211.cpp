#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int smax;
        string s;
        cin >> smax >> s;
        int standing = s[0] - '0';
        int need = 0;
        for (int i = 1; i <= smax; i++) {
            if (standing < i) {
                need += i - standing;
                standing = i;
            }
            standing += s[i] - '0';
        }
        cout << "Case #" << tc << ": " << need << "\n";
    }
    return 0;
}
