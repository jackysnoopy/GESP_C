#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
vector<string> split(string s) {
    vector<string> res;
    istringstream iss(s);
    string word;
    while (iss >> word) res.push_back(word);
    return res;
}
int match(vector<string> &t, vector<string> &p, int start) {
    int j = 0;
    for (int i = start; i < (int)t.size() && j < (int)p.size(); i++) {
        if (t[i] == p[j]) j++;
    }
    return j == (int)p.size() ? 1 : 0;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string line;
    getline(cin, line);
    vector<string> T = split(line);
    string a, b, c;
    getline(cin, a); getline(cin, b); getline(cin, c);
    vector<string> A = split(a), B = split(b), C = split(c);
    int n = T.size();
    vector<int> preA(n + 1, -1);
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (j < (int)A.size() && T[i] == A[j]) j++;
        preA[i + 1] = j == (int)A.size() ? i - (int)A.size() + 1 : -1;
    }
    vector<int> sufC(n + 2, -1);
    j = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (j < (int)C.size() && T[i] == C[(int)C.size() - 1 - j]) j++;
        sufC[i] = j == (int)C.size() ? i : -1;
    }
    int ans = n;
    for (int i = 0; i <= n; i++) {
        if (preA[i] == -1) continue;
        int endA = preA[i] + (int)A.size() - 1;
        for (int j = endA + 1; j <= n; j++) {
            if (sufC[j] == -1) continue;
            int startC = sufC[j];
            if (startC <= endA) continue;
            int kept = (int)A.size() + (int)C.size();
            int bpos = endA + 1;
            int bi = 0;
            for (int k = bpos; k < startC && bi < (int)B.size(); k++) {
                if (T[k] == B[bi]) bi++;
            }
            if (bi == (int)B.size()) kept += (int)B.size();
            int del = n - kept;
            ans = min(ans, del);
        }
    }
    cout << ans << endl;
    return 0;
}