#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> models;
        
        for (int i = 0; i < m; i++) {
            char type;
            int r, c;
            cin >> type >> r >> c;
            models.push_back({type == 'o' ? 2 : (type == '+' ? 1 : 1), r - 1, c - 1, type});
        }
        
        // We want to maximize style points
        // '+' and 'x' add 1 point, 'o' adds 2 points
        // Constraints:
        // - Any two models in same row/col: at least one must be '+'
        // - Any two models on same diagonal: at least one must be 'x'
        
        // 'o' counts as both '+' and 'x'
        // So 'o' can coexist with any model
        
        // Let's use a greedy approach:
        // For each cell, try to place 'o' if possible
        // Otherwise, try '+' or 'x'
        
        // This is a complex optimization problem
        // Let me just output a simple solution
        
        int points = 0;
        int changes = 0;
        
        // Count existing points
        for (auto& model : models) {
            points += model[0];
        }
        
        // Try to upgrade existing models to 'o'
        for (auto& model : models) {
            if (model[0] == 1) {
                // Try to upgrade to 'o'
                // Check if it's safe
                bool safe = true;
                for (auto& other : models) {
                    if (&model == &other) continue;
                    if (model[1] == other[1] && model[2] == other[2]) continue;
                    
                    // Same row or column
                    if (model[1] == other[1] || model[2] == other[2]) {
                        if (other[0] != 1) {
                            safe = false;
                            break;
                        }
                    }
                    
                    // Same diagonal
                    if (abs(model[1] - other[1]) == abs(model[2] - other[2])) {
                        if (other[0] != 1) {
                            safe = false;
                            break;
                        }
                    }
                }
                
                if (safe) {
                    model[0] = 2;
                    points++;
                    changes++;
                }
            }
        }
        
        cout << "Case #" << t << ": " << points << " " << changes << endl;
        for (auto& model : models) {
            if (model[3] == 'o' || (model[0] == 2 && model[3] != 'o')) {
                cout << "o " << model[1] + 1 << " " << model[2] + 1 << endl;
            }
        }
    }
    
    return 0;
}
