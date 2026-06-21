#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        long long D;
        string P;
        cin >> D >> P;
        int n = P.size();
        // Greedy: move s's before c's to reduce damage
        // Each s after all c's contributes power of 2^(num_c_before)
        vector<int> shoots;
        int ccount = 0;
        for (int i = 0; i < n; i++) {
            if (P[i] == 'c') ccount++;
            else shoots.push_back(ccount);
        }
        sort(shoots.rbegin(), shoots.rend());
        long long damage = 0;
        for (int i = 0; i < n; i++) {
            if (P[i] == 's') damage += (1LL << ccount);
            else damage += 0; // c doesn't directly add damage
        }
        // Actually: total damage = sum of 2^(#c before each s)
        damage = 0;
        int cs = 0;
        for (int i = 0; i < n; i++) {
            if (P[i] == 'c') cs++;
            else damage += (1LL << cs);
        }
        if (damage <= D) {
            cout << "Case #" << tc << ": 0\n";
            continue;
        }
        // Count total c's
        int totalC = 0;
        for (int i = 0; i < n; i++) if (P[i] == 'c') totalC++;
        // Shoots sorted by their c-count (high to low)
        // Each swap moves an s one position left past a c, reducing its c-count by 1
        int swaps = 0;
        sort(shoots.rbegin(), shoots.rend());
        for (int i = 0; i < (int)shoots.size(); i++) {
            if (damage <= D) break;
            if (shoots[i] == 0) break;
            damage -= (1LL << shoots[i]) - (1LL << (shoots[i] - 1));
            shoots[i]--;
            swaps++;
        }
        if (damage <= D) {
            cout << "Case #" << tc << ": " << swaps << "\n";
        } else {
            cout << "Case #" << tc << ": IMPOSSIBLE\n";
        }
    }
    return 0;
}
