#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        
        vector<int> L(n), R(n);
        for (int i = 0; i < n; i++) cin >> L[i];
        for (int i = 0; i < n; i++) cin >> R[i];
        
        // We have 13 mascots: ACDEHIJKMORST
        // We need to assign one mascot to each room
        // such that any three consecutive rooms have different mascots
        
        // This is equivalent to: for each room i, mascot[i] != mascot[L[i]] and mascot[i] != mascot[R[i]]
        // and for each room i, mascot[L[i]] != mascot[R[i]]
        
        // Wait, the constraint is: any three consecutive rooms have different mascots
        // This means: for any path of length 3, all three rooms have different mascots
        
        // Let's think about this as a graph coloring problem
        // Each room is a node
        // We need to color with 13 colors such that:
        // For any path of length 3, all three nodes have different colors
        
        // This is equivalent to: for each node i, its color is different from
        // the colors of all nodes at distance 1 and 2 from i
        
        // Let's try a greedy coloring
        vector<int> color(n, -1);
        
        // Color nodes in order
        for (int i = 0; i < n; i++) {
            // Find the set of forbidden colors
            vector<bool> forbidden(13, false);
            
            // Distance 1: L[i] and R[i]
            if (color[L[i]] != -1) forbidden[color[L[i]]] = true;
            if (color[R[i]] != -1) forbidden[color[R[i]]] = true;
            
            // Distance 2: L[L[i]], R[L[i]], L[R[i]], R[R[i]]
            if (color[L[L[i]]] != -1) forbidden[color[L[L[i]]]] = true;
            if (color[R[L[i]]] != -1) forbidden[color[R[L[i]]]] = true;
            if (color[L[R[i]]] != -1) forbidden[color[L[R[i]]]] = true;
            if (color[R[R[i]]] != -1) forbidden[color[R[R[i]]]] = true;
            
            // Find the first available color
            for (int c = 0; c < 13; c++) {
                if (!forbidden[c]) {
                    color[i] = c;
                    break;
                }
            }
            
            if (color[i] == -1) {
                // No valid color found
                break;
            }
        }
        
        string result = "";
        bool valid = true;
        
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                valid = false;
                break;
            }
            result += "ACDEHIJKMORST"[color[i]];
        }
        
        if (!valid) {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << t << ": " << result << endl;
        }
    }
    
    return 0;
}
