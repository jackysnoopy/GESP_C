#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        // Minimum number of moves for n disks = 2^n - 1
        // Number of digits in (2^n - 1)
        int digits = (int)(n * log10(2.0)) + 1;
        cout << digits << endl;
    }
    return 0;
}
