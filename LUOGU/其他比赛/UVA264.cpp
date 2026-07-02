#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int k = 1;
        while (k * (k + 1) / 2 < n) k++;
        int prev = (k - 1) * k / 2;
        int pos = n - prev;
        int num, den;
        if (k % 2 == 0) {
            num = pos;
            den = k - pos + 1;
        } else {
            num = k - pos + 1;
            den = pos;
        }
        cout << "The " << n << "th term is " << num << "/" << den << "." << endl;
    }
    return 0;
}
