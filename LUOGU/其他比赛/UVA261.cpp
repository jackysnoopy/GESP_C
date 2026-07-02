#include <iostream>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int a, b, c;
    while (cin >> a >> b >> c) {
        if (a > b) swap(a, b);
        if (c > b) {
            cout << "no" << endl;
        } else if (c == 0 || c % gcd(a, b) == 0) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}
