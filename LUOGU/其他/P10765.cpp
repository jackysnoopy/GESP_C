#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n;
        int k;
        cin >> n >> k;
        long long lo = 1, hi = n;
        for (int i = 0; i < k; i++) {
            int op;
            cin >> op;
            long long len = hi - lo + 1;
            if (op == 1) {
                lo = (lo + 1) / 2;
                lo += (len / 2);
                lo = lo;
            } else {
                lo = (lo + 1) / 2;
            }
            hi = lo;
            long long cnt = 1;
            long long tmp_lo = lo, tmp_hi = hi;
            for (int j = i + 1; j < k; j++) {
                int op2;
                cin >> op2;
                cnt *= 2;
            }
            // consume remaining ops
            for (int j = i + 1; j < k; j++) {
                int op2;
                cin >> op2;
            }
            break;
        }
        cout << lo << "\n";
    }
    return 0;
}
