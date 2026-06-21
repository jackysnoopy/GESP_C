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
        int D, S;
        cin >> D >> S;

        vector<int> C(S), E(S);
        for (int i = 0; i < S; i++) cin >> C[i] >> E[i];

        long long total_c = 0, total_e = 0;
        for (int i = 0; i < S; i++) {
            total_c += C[i];
            total_e += E[i];
        }

        string result = "";
        for (int i = 0; i < D; i++) {
            long long A, B;
            cin >> A >> B;

            bool possible = false;
            if (A <= total_c && B <= total_e) {
                possible = true;
            }

            result += (possible ? "Y" : "N");
        }

        cout << "Case #" << t << ": " << result << "\n";
    }

    return 0;
}
