#include <iostream>
#include <vector>
using namespace std;

bool isPythagorean(long long a, long long b, long long c) {
    return a * a + b * b == c * c;
}

int main() {
    long long n;
    while (cin >> n && n != 0) {
        long long count = 0;
        for (long long a = 1; a <= n; a++) {
            for (long long b = a; b <= n; b++) {
                long long c2 = a * a + b * b;
                long long c = (long long)sqrt((double)c2);
                if (c <= n && c * c == c2) {
                    count++;
                }
            }
        }
        cout << count << endl;
    }
    return 0;
}
