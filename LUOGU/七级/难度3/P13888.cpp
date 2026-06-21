#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int D;
    cin >> D;
    while (D--) {
        string T, S;
        cin >> T >> S;
        int n = S.size();
        if (S[0] != T[0] || S[n-1] != T[n-1]) { cout << -1 << "\n"; continue; }
        long long ans = 0;
        int runLen = 0;
        bool possible = true;
        for (int i = 0; i < n - 1; i++) {
            bool sBound = (S[i] != S[i+1]);
            bool tBound = (T[i] != T[i+1]);
            if (tBound && !sBound) { possible = false; break; }
            if (sBound && !tBound) {
                runLen++;
            } else {
                if (runLen % 2 != 0) { possible = false; break; }
                ans += runLen / 2;
                runLen = 0;
            }
        }
        if (runLen % 2 != 0) possible = false;
        ans += runLen / 2;
        cout << (possible ? ans : -1) << "\n";
    }
    return 0;
}
