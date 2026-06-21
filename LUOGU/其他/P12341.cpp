#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    int cntB = 0;
    int cntA = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') cntB++;
    }
    int bUsed = 0;
    int aRemaining = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') bUsed++;
        else {
            if (bUsed > 0) bUsed--;
            else aRemaining++;
        }
    }
    cout << aRemaining << "\n";
    return 0;
}
