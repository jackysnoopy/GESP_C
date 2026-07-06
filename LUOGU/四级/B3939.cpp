#include <iostream>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int A, B;
    cin >> A >> B;
    for (int i = A; i <= B; i++) {
        int rev = (i % 10) * 10 + (i / 10);
        if (isPrime(i) && isPrime(rev)) {
            cout << i << endl;
        }
    }
    return 0;
}
