#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string result;
    for (char c : s) {
        if (c >= 'a' && c <= 'z') result += c;
    }

    cout << result << "\n";
    return 0;
}
