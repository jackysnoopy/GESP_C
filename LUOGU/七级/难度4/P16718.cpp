#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    string S;
    cin >> S;

    vector<int> prefix(N + 1, 0);
    for (int i = 0; i < N - 1; i++) {
        prefix[i + 1] = prefix[i] + (S[i] == '<' ? 1 : -1);
    }

    while (M--) {
        int L, R;
        cin >> L >> R;
        L--; R--;

        int min_val = prefix[L];
        int max_val = prefix[L];
        for (int i = L; i <= R + 1; i++) {
            min_val = min(min_val, prefix[i]);
            max_val = max(max_val, prefix[i]);
        }

        cout << max_val - min_val + 1 << "\n";
    }

    return 0;
}
