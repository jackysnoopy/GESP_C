#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long l, r;
    cin >> l >> r;
    long long sum = 0;
    for (long long i = l; i <= r; i++) {
        if (__builtin_popcountll(i) & 1) sum += i;
    }
    cout << sum << "\n";
    return 0;
}
