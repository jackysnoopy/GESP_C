// UVA136 - Ugly Numbers (丑数)
// 丑数：只能被2,3,5整除的数
// 第1500个丑数是859963392
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    const int N = 1500;
    vector<long long> ugly(N);
    ugly[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;
    for (int i = 1; i < N; i++) {
        long long next2 = ugly[i2] * 2;
        long long next3 = ugly[i3] * 3;
        long long next5 = ugly[i5] * 5;
        long long next = min({next2, next3, next5});
        ugly[i] = next;
        if (next == next2) i2++;
        if (next == next3) i3++;
        if (next == next5) i5++;
    }
    cout << "The 1500'th ugly number is " << ugly[N - 1] << "." << endl;
    return 0;
}
