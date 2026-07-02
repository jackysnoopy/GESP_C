#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int h, k;
vector<int> stamps;
vector<int> best;
int maxVal = 0;

void dfs(int pos, int depth, int sum, int prev) {
    if (depth == h) {
        if (sum > maxVal) {
            maxVal = sum;
            best = stamps;
        }
        return;
    }
    for (int i = 1; i <= k; i++) {
        if (depth + i > h) break;
        int newSum = sum;
        vector<int> newStamps = stamps;
        for (int j = 0; j < i; j++) {
            newSum += prev;
            newStamps.push_back(prev);
        }
        dfs(pos + 1, depth + i, newSum, newSum);
    }
}

int main() {
    while (cin >> h >> k && (h || k)) {
        stamps.clear();
        stamps.push_back(1);
        maxVal = 0;
        dfs(1, 1, 1, 1);
        
        for (int i = 0; i < h; i++) {
            if (i) cout << " ";
            cout << best[i];
        }
        cout << " " << maxVal << "\n";
    }
    return 0;
}
