#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        long long B;
        cin >> B >> N;

        vector<long long> X(N);
        for (int i = 0; i < N; i++) cin >> X[i];

        long long total_other = 0;
        for (int i = 0; i < N; i++) total_other += X[i];

        long long empty = 37 - N;

        if (empty == 0) {
            cout << "Case #" << t << ": 0\n";
            continue;
        }

        double prob = (double)empty / 37.0;
        double expected = prob * 36.0;

        long long bet = min(B, (long long)empty);
        double profit = expected * bet - bet;

        cout << "Case #" << t << ": " << fixed << setprecision(10) << profit << "\n";
    }

    return 0;
}
