#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    // Railway on 8-shaped track
    // Two loops sharing intersection
    // Place n lamps with colors 1..k
    // One lamp at intersection
    // Adjacent lamps must have different colors
    // Upper and lower branches each have at least 2 lamps (excluding intersection)
    
    // Read lamp colors
    vector<int> colors(n);
    vector<int> count(k + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> colors[i];
        count[colors[i]]++;
    }
    
    // Check if solution exists
    // Key constraint: adjacent lamps different colors
    // This is a graph coloring problem on a cycle
    
    // For the upper branch (x lamps) and lower branch (y lamps)
    // x + y + 1 = n, x >= 2, y >= 2
    
    // Each branch forms a path from intersection
    // The two branches together form two cycles sharing the intersection
    
    // For a cycle of length L, we need at least 2 colors
    // And no color can appear more than L/2 times
    
    // Try to find a valid arrangement
    // For simplicity, check if we have enough colors
    
    int maxCount = *max_element(count.begin() + 1, count.end());
    
    if (maxCount > n / 2) {
        cout << "-1\n";
        return 0;
    }
    
    // Construct a valid arrangement
    // Place intersection lamp with color 1
    // Alternate colors on each branch
    
    int x = (n - 1) / 2;
    int y = n - 1 - x;
    
    if (x < 2 || y < 2) {
        x = 2;
        y = n - 3;
        if (y < 2) {
            cout << "-1\n";
            return 0;
        }
    }
    
    cout << x << " " << y << "\n";
    
    // Output upper branch
    for (int i = 0; i < x; i++) {
        cout << (i % 2 == 0 ? 1 : 2) << (i + 1 < x ? " " : "\n");
    }
    
    // Intersection color
    cout << "3\n";
    
    // Output lower branch
    for (int i = 0; i < y; i++) {
        cout << (i % 2 == 0 ? 1 : 2) << (i + 1 < y ? " " : "\n");
    }
    
    return 0;
}
