#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    while (cin >> a >> b) {
        cout << a << " / " << b << " = ";

        map<int, int> pos;
        vector<int> digits;
        int rem = a % b;
        int idx = 0;

        while (rem != 0 && pos.find(rem) == pos.end()) {
            pos[rem] = idx++;
            rem *= 10;
            digits.push_back(rem / b);
            rem %= b;
        }

        if (rem == 0) {
            cout << ".";
            for (int d : digits) cout << d;
            cout << "\n";
        } else {
            int start = pos[rem];
            cout << ".";
            for (int i = 0; i < start; i++) cout << digits[i];
            cout << "(";
            int len = 0;
            for (int i = start; i < (int)digits.size(); i++) {
                cout << digits[i];
                len++;
            }
            cout << ")\n";
            if (len > 50) {
                cout << "Too many decimal digits.\n";
            }
        }
        cout << "\n";
    }

    return 0;
}
