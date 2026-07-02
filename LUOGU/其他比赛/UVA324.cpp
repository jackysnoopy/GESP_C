#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<int> factorial(1, 1);
        for (int i = 2; i <= n; i++) {
            int carry = 0;
            for (int j = 0; j < (int)factorial.size(); j++) {
                int prod = factorial[j] * i + carry;
                factorial[j] = prod % 10;
                carry = prod / 10;
            }
            while (carry) {
                factorial.push_back(carry % 10);
                carry /= 10;
            }
        }

        int cnt[10] = {0};
        for (int d : factorial) {
            cnt[d]++;
        }

        cout << n << "! --" << endl;
        for (int i = 0; i < 10; i++) {
            if (i % 5 == 0) cout << "    ";
            else cout << "    ";
            cout << "(" << i << ")" << "    " << cnt[i];
            if (i % 5 == 4) cout << endl;
        }
        cout << endl;
    }
    return 0;
}
