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
        int depth = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int d = s[i] - '0';
            while (depth < d) { result += '('; depth++; }
            while (depth > d) { result += ')'; depth--; }
            result += s[i];
        }
        while (depth > 0) { result += ')'; depth--; }
        cout << "Case #" << tc << ": " << result << "\n";
    }
    return 0;
}
