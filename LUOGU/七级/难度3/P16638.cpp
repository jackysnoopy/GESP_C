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

    int evenCount = 0;
    for (char c : s) {
        if ((c - '0') % 2 == 0) evenCount++;
    }

    cout << evenCount << "\n";
    return 0;
}
