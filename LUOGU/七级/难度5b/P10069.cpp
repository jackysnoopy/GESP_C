#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int solve(string S, string T) {
    int n = S.size();
    int m = T.size();

    if (m == 1) {
        char c = T[0];
        for (int i = 0; i < n; i++) {
            if (S[i] == c) return -1;
        }
        return 0;
    }

    if (m == 2) {
        bool hasT = false;
        for (int i = 0; i + 1 < n; i++) {
            if (S[i] == T[0] && S[i + 1] == T[1]) {
                hasT = true;
                break;
            }
        }
        if (!hasT) return 0;

        if (T[0] == T[1]) {
            char c = T[0];
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c) cnt++;
            }
            int other = n - cnt;
            if (cnt > other + 1) return -1;
            int runs = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c && (i == 0 || S[i - 1] != c)) runs++;
            }
            if (runs <= 1) return 1;
            return 2;
        } else {
            int cntA = 0, cntB = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == T[0]) cntA++;
                if (S[i] == T[1]) cntB++;
            }
            if (cntA == 0 || cntB == 0) return 0;

            string target = string(cntB, T[1]) + string(cntA, T[0]);
            int runs = 1;
            for (int i = 1; i < n; i++) {
                if (S[i] != S[i - 1]) runs++;
            }
            if (S[0] == T[1]) {
                return (runs - 1) / 2;
            } else {
                return runs / 2;
            }
        }
    }

    if (m == 3) {
        bool hasT = false;
        for (int i = 0; i + 2 < n; i++) {
            if (S[i] == T[0] && S[i + 1] == T[1] && S[i + 2] == T[2]) {
                hasT = true;
                break;
            }
        }
        if (!hasT) return 0;

        if (T[0] == T[1] && T[1] == T[2]) {
            char c = T[0];
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c) cnt++;
            }
            int other = n - cnt;
            if (cnt > other * 2 + 2) return -1;
            int runs = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c && (i == 0 || S[i - 1] != c)) runs++;
            }
            return min(runs, 3);
        }

        if (T[0] == T[1] && T[1] != T[2]) {
            char c = T[0], d = T[2];
            int cntC = 0, cntD = 0, cntOther = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c) cntC++;
                else if (S[i] == d) cntD++;
                else cntOther++;
            }
            if (cntC == 0 || cntD == 0) return 0;
            if (cntC > cntD + cntOther + 1) return -1;
            return 1;
        }

        if (T[0] != T[1] && T[1] == T[2]) {
            char a = T[0], c = T[1];
            int cntA = 0, cntC = 0, cntOther = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == a) cntA++;
                else if (S[i] == c) cntC++;
                else cntOther++;
            }
            if (cntA == 0 || cntC == 0) return 0;
            if (cntC > cntA + cntOther + 1) return -1;
            return 1;
        }

        if (T[0] != T[1] && T[0] != T[2] && T[1] != T[2]) {
            int cnt[3] = {0, 0, 0};
            for (int i = 0; i < n; i++) {
                if (S[i] == T[0]) cnt[0]++;
                else if (S[i] == T[1]) cnt[1]++;
                else if (S[i] == T[2]) cnt[2]++;
            }
            if (cnt[0] == 0 || cnt[1] == 0 || cnt[2] == 0) return 0;
            return 1;
        }

        int cnt[26] = {0};
        for (int i = 0; i < n; i++) cnt[S[i] - 'a']++;
        int runs = 1;
        for (int i = 1; i < n; i++) {
            if (S[i] != S[i - 1]) runs++;
        }
        return min(runs, 3);
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        string S, T;
        cin >> S >> T;
        cout << solve(S, T) << "\n";
    }
    return 0;
}
