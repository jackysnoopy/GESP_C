#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, n;
    cin >> T >> n;
    
    while (T--) {
        long long m;
        cin >> m;
        
        vector<vector<long long>> enemy(n);
        for (int i = 0; i < n; i++) {
            int l;
            cin >> l;
            enemy[i].resize(l);
            for (int j = 0; j < l; j++) {
                cin >> enemy[i][j];
            }
        }
        
        if (m == 0) {
            long long score = 0;
            for (int i = 0; i < n; i++) {
                for (long long x : enemy[i]) score += x;
            }
            cout << score << "\n";
            continue;
        }
        
        long long ans = 0;
        
        for (int i = 0; i < n; i++) {
            long long myScore = 0;
            long long enemyScore = 0;
            
            vector<long long> myPieces;
            long long remaining = m;
            
            for (int j = 0; j < (int)enemy[i].size(); j++) {
                if (remaining > 0) {
                    long long piece = min(remaining, enemy[i][j]);
                    myPieces.push_back(piece);
                    remaining -= piece;
                }
            }
            
            int pi = 0, ei = 0;
            while (pi < (int)myPieces.size() && ei < (int)enemy[i].size()) {
                if (myPieces[pi] == enemy[i][ei]) {
                    myPieces[pi] = 0;
                    enemy[i][ei] = 0;
                    pi++;
                    ei++;
                } else if (myPieces[pi] > enemy[i][ei]) {
                    myPieces[pi]--;
                    enemy[i][ei] = 0;
                    ei++;
                } else {
                    enemy[i][ei]--;
                    myPieces[pi] = 0;
                    pi++;
                }
            }
            
            for (int j = pi; j < (int)myPieces.size(); j++) {
                myScore += myPieces[j];
            }
            for (int j = ei; j < (int)enemy[i].size(); j++) {
                enemyScore += enemy[i][j];
            }
            
            ans += enemyScore;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
