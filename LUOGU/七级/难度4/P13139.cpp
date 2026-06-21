#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, L;
        cin >> N >> L;

        vector<int> C(L);
        int sum = 0;
        for (int i = 0; i < L; i++) {
            cin >> C[i];
            sum += C[i];
        }

        int remaining = N - sum;
        int base = 0;
        vector<double> frac;

        for (int i = 0; i < L; i++) {
            double pct = 100.0 * C[i] / N;
            base += (int)floor(pct + 0.5);
            double rem = pct - floor(pct);
            if (rem >= 0.5 - 1e-9) {
                frac.push_back(ceil(pct) - pct);
            } else {
                frac.push_back(0.5 - rem);
            }
        }

        sort(frac.begin(), frac.end());

        int ans = base;
        int extra = 0;
        for (int i = 0; i < remaining; i++) {
            if (i < (int)frac.size() && frac[i] <= 1e-9) {
                extra++;
            } else if (i < (int)frac.size()) {
                double need = frac[i];
                if (need <= 1.0 / N + 1e-9) {
                    extra++;
                }
            }
        }

        cout << "Case #" << t << ": " << ans + extra << "\n";
    }

    return 0;
}
