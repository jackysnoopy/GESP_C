#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<vector<int>> snowflakes;
        for (int i = 0; i < n; i++) {
            vector<int> s(6);
            for (int j = 0; j < 6; j++) cin >> s[j];
            snowflakes.push_back(s);
        }
        set<vector<int>> seen;
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            vector<int>& s = snowflakes[i];
            // Generate all 12 representations (6 rotations x 2 reflections)
            for (int rot = 0; rot < 6; rot++) {
                vector<int> cur(6);
                for (int j = 0; j < 6; j++) cur[j] = s[(j + rot) % 6];
                if (seen.count(cur)) { found = true; break; }
                seen.insert(cur);
                // Reflection: reverse the order
                vector<int> ref(6);
                for (int j = 0; j < 6; j++) ref[j] = cur[5 - j];
                if (seen.count(ref)) { found = true; break; }
                seen.insert(ref);
            }
        }
        cout << (found ? "Twin snowflakes found." : "No two snowflakes are alike.") << endl;
    }
    return 0;
}
