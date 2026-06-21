#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    cin >> N;
    bool first = true;
    for (long long p = 2; p * p <= N; p++) {
        if (N % p == 0) {
            int cnt = 0;
            while (N % p == 0) { N /= p; cnt++; }
            if (!first) cout << " * ";
            cout << p;
            if (cnt > 1) cout << "^" << cnt;
            first = false;
        }
    }
    if (N > 1) {
        if (!first) cout << " * ";
        cout << N;
    }
    cout << endl;
    return 0;
}
