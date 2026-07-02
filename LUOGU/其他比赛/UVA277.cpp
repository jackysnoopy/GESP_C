#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

int cost[26][26];

int main() {
    int T;
    cin >> T;
    bool first = true;
    while (T--) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                cin >> cost[i][j];
            }
        }
        
        string s;
        cin >> s;
        int n = s.length();
        
        string result = "";
        int i = 0;
        while (i < n) {
            int c = s[i] - 'A';
            int best = INF;
            int bestOp = -1;
            
            for (int j = 0; j < 26; j++) {
                if (cost[c][j] < best) {
                    best = cost[c][j];
                    bestOp = j;
                }
            }
            
            if (i + 1 < n) {
                int c2 = s[i + 1] - 'A';
                if (cost[c][c2] < best) {
                    result += s[i];
                    i++;
                    continue;
                }
            }
            
            result += (char)('A' + bestOp);
            i++;
        }
        
        if (!first) cout << "\n";
        first = false;
        cout << result << "\n";
    }
    return 0;
}
