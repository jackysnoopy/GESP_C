#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << "\n";
        first = false;
        vector<int> heights(n);
        for (int i = 0; i < n; i++) cin >> heights[i];
        
        vector<int> result;
        result.push_back(heights[0]);
        for (int i = 1; i < n; i++) {
            if (heights[i] > result.back()) {
                result.push_back(heights[i]);
            } else {
                *lower_bound(result.begin(), result.end(), heights[i]) = heights[i];
            }
        }
        
        cout << result.size() << "\n";
    }
    return 0;
}
