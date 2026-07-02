#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    bool firstCase = true;

    while (cin >> n && n) {
        vector<vector<long long>> mat(n, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> mat[i][j];
            }
        }

        long long globalMax = LLONG_MIN;

        for (int top = 0; top < n; top++) {
            vector<long long> colSum(n, 0);
            for (int bottom = top; bottom < n; bottom++) {
                for (int j = 0; j < n; j++) {
                    colSum[j] += mat[bottom][j];
                }

                long long maxEndingHere = colSum[0];
                long long maxSoFar = colSum[0];
                for (int j = 1; j < n; j++) {
                    maxEndingHere = max(colSum[j], maxEndingHere + colSum[j]);
                    maxSoFar = max(maxSoFar, maxEndingHere);
                }
                globalMax = max(globalMax, maxSoFar);
            }
        }

        if (!firstCase) cout << endl;
        firstCase = false;
        cout << globalMax << endl;
    }

    return 0;
}
