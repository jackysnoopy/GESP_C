#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;

        vector<string> towers(n);
        for (int i = 0; i < n; i++) cin >> towers[i];

        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;

        bool found = false;
        string result;

        do {
            string megatower;
            for (int i : order) megatower += towers[i];

            bool valid = true;
            for (char c = 'A'; c <= 'Z'; c++) {
                int first = -1, last = -1;
                for (int i = 0; i < (int)megatower.size(); i++) {
                    if (megatower[i] == c) {
                        if (first == -1) first = i;
                        last = i;
                    }
                }
                if (first != -1) {
                    for (int i = first; i <= last; i++) {
                        if (megatower[i] != c) {
                            valid = false;
                            break;
                        }
                    }
                }
                if (!valid) break;
            }

            if (valid) {
                result = megatower;
                found = true;
                break;
            }
        } while (next_permutation(order.begin(), order.end()));

        cout << "Case #" << t << ": ";
        if (found) cout << result << "\n";
        else cout << "IMPOSSIBLE\n";
    }

    return 0;
}
