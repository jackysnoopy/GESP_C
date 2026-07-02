#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int X, Y;
        cin >> X >> Y;
        
        int ax = abs(X), ay = abs(Y);
        
        // Find minimum n such that S = n(n+1)/2 >= ax+ay and S%2 == (ax+ay)%2
        int n = 0;
        long long S = 0;
        int target = ax + ay;
        while (S < target || (S - target) % 2 != 0) {
            n++;
            S += n;
        }
        
        // excess = (S - target) / 2, need to represent as sum of some subset of {1..n}
        int excess = (int)((S - target) / 2);
        
        // Greedy: assign jumps toward target, flip some to cancel excess
        string result = "";
        int cx = 0, cy = 0;
        
        // First, determine direction for each jump
        // We'll greedily move toward (ax, ay) then fix
        vector<int> dir(n + 1, 0); // 0=unused, 1=toward X, 2=toward Y
        
        int remX = ax, remY = ay;
        for (int i = n; i >= 1; i--) {
            if (remX >= remY && remX > 0) {
                dir[i] = 1;
                remX -= i;
            } else if (remY > 0) {
                dir[i] = 2;
                remY -= i;
            }
        }
        // remaining goes to whichever has deficit
        remX = ax; remY = ay;
        for (int i = 1; i <= n; i++) {
            if (dir[i] == 0) {
                if (remX > 0) { dir[i] = 1; remX -= i; }
                else { dir[i] = 2; remY -= i; }
            } else if (dir[i] == 1) {
                remX -= i;
            } else {
                remY -= i;
            }
        }
        
        // Now fix: excess = (S-target)/2 means we need to flip jumps summing to excess
        // to opposite direction. We flip from the greedy assignment.
        // Actually, let's use a cleaner approach.
        
        // Simpler approach: assign all jumps, then flip subset summing to excess
        cx = 0; cy = 0;
        vector<int> jumps(n + 1);
        for (int i = 1; i <= n; i++) jumps[i] = i;
        
        // Greedy forward: assign toward X then Y
        int needX = ax, needY = ay;
        vector<bool> useX(n + 1, false);
        for (int i = n; i >= 1; i--) {
            if (needX >= i) {
                useX[i] = true;
                needX -= i;
            } else if (needY >= i) {
                needY -= i;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (needX > 0 && !useX[i] && i <= needX) {
                useX[i] = true;
                needX -= i;
            }
        }
        
        // Final assignment
        result = "";
        for (int i = 1; i <= n; i++) {
            if (useX[i]) {
                result += (X >= 0) ? "E" : "W";
            } else {
                result += (Y >= 0) ? "N" : "S";
            }
        }
        
        cout << "Case #" << t << ": " << result << "\n";
    }
    
    return 0;
}