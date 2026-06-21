#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<string> grid(N);
        for (int i = 0; i < N; i++) cin >> grid[i];
        // Find rightmost 1 in each row
        vector<int> rightmost(N);
        for (int i = 0; i < N; i++) {
            rightmost[i] = -1;
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '1') rightmost[i] = j;
            }
        }
        // Greedy: place rows from top to bottom
        // Row i needs rightmost <= i
        int ans = 0;
        for (int i = 0; i < N; i++) {
            // Find a row with rightmost <= i among remaining rows
            // Pick the one with the largest rightmost (greedy)
            int best = -1, bestIdx = -1;
            for (int j = i; j < N; j++) {
                if (rightmost[j] <= i) {
                    if (bestIdx == -1 || rightmost[j] > best) {
                        best = rightmost[j];
                        bestIdx = j;
                    }
                }
            }
            // Swap row bestIdx to position i
            if (bestIdx != i) {
                for (int j = bestIdx; j > i; j--) {
                    swap(rightmost[j], rightmost[j-1]);
                    ans++;
                }
            }
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
