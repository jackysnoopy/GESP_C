#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int maxSum = 0, curSum = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int val = (s[i] == '0') ? 1 : -1;
        curSum = max(val, curSum + val);
        maxSum = max(maxSum, curSum);
    }
    cout << maxSum << "\n";
    return 0;
}
