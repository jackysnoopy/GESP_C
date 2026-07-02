#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t = 0;
    while (true) {
        vector<int> missiles;
        int h;
        while (cin >> h && h != -1) {
            missiles.push_back(h);
        }
        if (missiles.empty()) break;
        if (t++) cout << "\n";
        int n = missiles.size();
        vector<int> lis(n, 1), parent(n, -1);
        int maxLen = 1, maxEnd = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (missiles[j] >= missiles[i] && lis[j] + 1 > lis[i]) {
                    lis[i] = lis[j] + 1;
                    parent[i] = j;
                }
            }
            if (lis[i] > maxLen) {
                maxLen = lis[i];
                maxEnd = i;
            }
        }
        cout << "Test #" << t << ":\n";
        cout << "  maximum possible interceptions: " << maxLen << "\n";
    }
    return 0;
}
