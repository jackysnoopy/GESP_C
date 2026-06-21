#include <iostream>
#include <algorithm>
using namespace std;

// Minimum cost to reach b from c using only *2 and +1
long long ascend(long long c, long long b) {
    if (c >= b) return c - b; // wait, can't subtract. If c == b, 0. If c > b, impossible.
    // Actually, c < b always in our use case.
    // Work backwards from b to c:
    // If b <= c: cost = 0 (b == c) or impossible (b < c)
    // If b is odd: cost = 1 + ascend(c, b-1)
    // If b is even and b/2 >= c: cost = 1 + ascend(c, b/2)
    // If b is even and b/2 < c: cost = 1 + ascend(c, b-1)
    long long cost = 0;
    while (b > c) {
        if (b % 2 == 1) {
            b--;
            cost++;
        } else if (b / 2 >= c) {
            b /= 2;
            cost++;
        } else {
            b--;
            cost++;
        }
    }
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        long long a, b;
        cin >> a >> b;
        long long result = (long long)4e18;
        
        if (a <= b) {
            result = ascend(a, b);
        } else {
            long long cur = a;
            long long dcost = 0;
            while (cur >= 1 && dcost < result) {
                if (cur <= b) {
                    result = min(result, dcost + ascend(cur, b));
                }
                if (cur % 2 == 1) { cur++; dcost++; }
                else { cur /= 2; dcost++; }
            }
        }
        
        cout << result << "\n";
    }
    return 0;
}
