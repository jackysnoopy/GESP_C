#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n && n != -1) {
        if (!first) cout << "\n";
        first = false;
        vector<int> digits;
        int tmp = n;
        while (tmp > 0) {
            digits.push_back(tmp % 10);
            tmp /= 10;
        }
        reverse(digits.begin(), digits.end());
        int len = digits.size();
        int cnt = 0;
        for (int i = 0; i < len; i++) {
            if (digits[i] != 0) cnt++;
        }
        cout << n << " is " << cnt << "-digital number.\n";
    }
    return 0;
}
