#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<double> naomi(N), ken(N);
        for (int i = 0; i < N; i++) cin >> naomi[i];
        for (int i = 0; i < N; i++) cin >> ken[i];

        sort(naomi.begin(), naomi.end());
        sort(ken.begin(), ken.end());

        int deceit = 0, war = 0;

        int i = 0, j = 0;
        while (i < N && j < N) {
            if (naomi[i] > ken[j]) {
                deceit++;
                j++;
            }
            i++;
        }

        i = 0, j = 0;
        while (i < N && j < N) {
            if (ken[j] > naomi[i]) {
                war++;
                i++;
            }
            j++;
        }

        cout << "Case #" << t << ": " << deceit << " " << N - war << "\n";
    }

    return 0;
}
