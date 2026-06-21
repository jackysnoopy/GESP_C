#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    string result = "";
    int open_needed = 0;
    for (char c : s) {
        if (c == '(') {
            open_needed++;
        } else {
            if (open_needed > 0) {
                open_needed--;
            }
        }
    }
    string prefix = "";
    for (int i = 0; i < open_needed; i++) prefix += "(";
    result = prefix + s;
    int bal = 0;
    string final_result = "";
    for (char c : result) {
        if (c == '(') {
            bal++;
        } else {
            bal--;
        }
        final_result += c;
    }
    for (int i = 0; i < bal; i++) final_result += ")";
    cout << final_result << "\n";
    return 0;
}
