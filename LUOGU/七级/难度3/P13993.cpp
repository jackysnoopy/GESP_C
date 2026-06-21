#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string result;
    for (char c : s) {
        if (c == 'z') c = 'a';
        else c++;
        result += c;
    }

    cout << result << "\n";
    return 0;
}
