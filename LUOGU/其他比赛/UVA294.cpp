#include <iostream>
#include <cmath>
using namespace std;

long long countDivisors(long long n) {
    long long count = 0;
    long long sqrt_n = (long long)sqrt((double)n);
    for (long long i = 1; i <= sqrt_n; i++) {
        if (n % i == 0) {
            count += 2;
            if (i * i == n) count--;
        }
    }
    return count;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long L, U;
        cin >> L >> U;
        long long maxDiv = 0;
        long long maxNum = L;
        for (long long i = L; i <= U; i++) {
            long long d = countDivisors(i);
            if (d > maxDiv) {
                maxDiv = d;
                maxNum = i;
            }
        }
        cout << "Between " << L << " and " << U << ", " << maxNum
             << " has a maximum of " << maxDiv << " divisors." << endl;
    }
    return 0;
}
