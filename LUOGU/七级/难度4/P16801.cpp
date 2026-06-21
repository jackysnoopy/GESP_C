#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    int ones = 0;
    for (char c : s) if (c == '1') ones++;

    string result = s;
    int pos = 0;

    for (int i = 0; i < n; i++) {
        if (result[i] == '0') {
            for (int j = i + 1; j < n; j++) {
                if (result[j] == '1') {
                    result[i] = '1';
                    result[j] = '0';
                    break;
                }
            }
        }
    }

    cout << result << "\n";
    return 0;
}
