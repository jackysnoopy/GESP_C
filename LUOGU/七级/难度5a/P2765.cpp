#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool isSquare(int x) {
    int s = sqrt(x);
    return s * s == x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // Greedy: try to place each ball on an existing pillar
    // If not possible, create a new pillar
    
    vector<vector<int>> pillars(n);
    
    for (int ball = 1; ball <= 1000; ball++) {
        bool placed = false;
        
        for (int i = 0; i < n; i++) {
            if (!pillars[i].empty() && isSquare(pillars[i].back() + ball)) {
                pillars[i].push_back(ball);
                placed = true;
                break;
            }
        }
        
        if (!placed) {
            // Find an empty pillar
            for (int i = 0; i < n; i++) {
                if (pillars[i].empty()) {
                    pillars[i].push_back(ball);
                    placed = true;
                    break;
                }
            }
        }
        
        if (!placed) {
            // All pillars are full, we can't place more balls
            break;
        }
    }
    
    // Find the maximum number of balls placed
    int max_balls = 0;
    for (int i = 0; i < n; i++) {
        max_balls = max(max_balls, (int)pillars[i].size());
    }
    
    cout << max_balls << "\n";
    
    // Output the placement
    for (int i = 0; i < n; i++) {
        if (!pillars[i].empty()) {
            for (int j = 0; j < (int)pillars[i].size(); j++) {
                cout << pillars[i][j] << (j == (int)pillars[i].size() - 1 ? "\n" : " ");
            }
        } else {
            cout << "\n";
        }
    }
    
    return 0;
}
