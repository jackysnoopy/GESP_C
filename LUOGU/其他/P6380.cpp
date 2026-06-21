#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b;
    string s;
    cin >> a >> b >> s;
    int len = s.size();
    int ans = -1;
    for (int first = 1; first <= 9; first++) {
        int rem = 0;
        string result;
        bool valid = true;
        int startPos = -1;
        for (int i = 0; i < len; i++) {
            rem = (rem * 10 + (s[i] - '0')) % a;
            if (rem == 0 && s[i] != '0' && startPos == -1) {
                startPos = i;
            }
        }
        if (startPos == -1) continue;
        rem = 0;
        result = "";
        for (int i = startPos; i < len; i++) {
            rem = (rem * 10 + (s[i] - '0')) % a;
            result += s[i];
        }
        if (rem != 0) continue;
        string target = "";
        for (int i = 0; i < b; i++) {
            target += s[i];
        }
        if (result.size() == (size_t)b && result.find(target) != string::npos) {
            ans = stoi(result);
        }
    }
    cout << ans << "\n";
    return 0;
}
