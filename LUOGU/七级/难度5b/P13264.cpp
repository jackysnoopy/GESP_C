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
        int N;
        cin >> N;
        
        vector<string> M(2 * N);
        for (int i = 0; i < 2 * N; i++) cin >> M[i];
        
        cout << "Case #" << t << ": ";
        
        // Check each row has exactly N 1s
        bool ok = true;
        for (int i = 0; i < 2 * N; i++) {
            int cnt = 0;
            for (char c : M[i]) cnt += (c == '1');
            if (cnt != N) { ok = false; break; }
        }
        
        if (!ok) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        
        // Classify rows by pattern
        vector<int> pat(2 * N, 0);
        for (int i = 0; i < 2 * N; i++) {
            for (int j = 0; j < 2 * N; j++) {
                if (M[i][j] == '1') pat[i] |= (1 << j);
            }
        }
        
        int p1 = -1, p2 = -1;
        vector<int> c1_pos, c2_pos;
        for (int i = 0; i < 2 * N; i++) {
            if (p1 == -1) { p1 = pat[i]; c1_pos.push_back(i); }
            else if (pat[i] == p1) { c1_pos.push_back(i); }
            else if (p2 == -1) { p2 = pat[i]; c2_pos.push_back(i); }
            else if (pat[i] == p2) { c2_pos.push_back(i); }
            else { ok = false; break; }
        }
        
        if (!ok || p2 == -1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        
        // Check complement
        int fullMask = (1 << (2 * N)) - 1;
        if ((p1 ^ p2) != fullMask) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        
        int ans = 2 * N;
        int fullEven = 0;
        for (int j = 0; j < 2 * N; j += 2) fullEven |= (1 << j);
        int fullOdd = fullMask ^ fullEven;
        
        // For each form and choice
        for (int form = 0; form < 2; form++) {
            int targetMask = (form == 0) ? fullOdd : fullEven;
            for (int choice = 0; choice < 2; choice++) {
                int typeAPat = (choice == 0) ? p1 : p2;
                vector<int>& typeARows = (choice == 0) ? c1_pos : c2_pos;
                int cA = typeARows.size();
                
                // Row swaps
                int evenCount = 0;
                for (int r : typeARows) if (r % 2 == 0) evenCount++;
                int rowSwaps = N - evenCount;
                
                // Column swaps
                int match = __builtin_popcount(typeAPat & targetMask);
                int colSwaps = N - match;
                
                ans = min(ans, rowSwaps + colSwaps);
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}