#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<long long> A(N + 1);
        for (int i = 1; i <= N; i++) cin >> A[i];
        int La, Ra, Lb, Rb;
        cin >> La >> Ra >> Lb >> Rb;
        vector<long long> pref(N + 2, 0);
        for (int i = 1; i <= N; i++) pref[i] = pref[i - 1] + A[i];
        vector<long long> suff(N + 2, 0);
        for (int i = N; i >= 1; i--) suff[i] = suff[i + 1] + A[i];
        long long best = 0;
        for (int a = La; a <= Ra; a++) {
            long long worst = LLONG_MAX;
            int b1 = max(Lb, a + 1);
            if (b1 <= Rb) {
                int g = b1 - a - 1;
                int split = a + (g + 1) / 2;
                worst = min(worst, pref[split]);
            }
            int b2 = min(Rb, a - 1);
            if (b2 >= Lb) {
                int g = a - b2 - 1;
                int split = a - (g + 1) / 2;
                worst = min(worst, suff[split]);
            }
            if (worst != LLONG_MAX) best = max(best, worst);
        }
        cout << "Case #" << tc << ": " << best << "\n";
    }
    return 0;
}
