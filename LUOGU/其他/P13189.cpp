#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        string result;
        for (int i = 0; i < (int)s.size(); i++) {
            if (result.empty() || s[i] >= result[0]) {
                result = s[i] + result;
            } else {
                result = result + s[i];
            }
        }
        cout << "Case #" << tc << ": " << result << "\n";
    }
    return 0;
}
