#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int count = 0;
        int x = n;
        while (x) {
            count += x & 1;
            x >>= 1;
        }
        cout << n << " has " << count << " bits and " 
             << (32 - count) << " zero bits" << endl;
    }
    return 0;
}
