#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int cas = 0;
    while (cin >> n && n) {
        vector<vector<double>> a(n, vector<double>(n + 1));
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= n; j++)
                cin >> a[i][j];

        cout << "Test Case " << ++cas << "\n";

        // Gaussian elimination with partial pivoting
        vector<int> where(n, -1);
        for (int col = 0, row = 0; col < n && row < n; col++) {
            int pivot = row;
            for (int i = row + 1; i < n; i++)
                if (fabs(a[i][col]) > fabs(a[pivot][col]))
                    pivot = i;
            if (fabs(a[pivot][col]) < EPS) continue;
            swap(a[row], a[pivot]);
            where[col] = row;

            for (int i = 0; i < n; i++) {
                if (i == row) continue;
                double factor = a[i][col] / a[row][col];
                for (int j = col; j <= n; j++)
                    a[i][j] -= factor * a[row][j];
            }
            row++;
        }

        // Check for no solution or infinite solutions
        bool noSolution = false;
        for (int i = 0; i < n; i++) {
            bool allZero = true;
            for (int j = 0; j < n; j++)
                if (fabs(a[i][j]) > EPS) { allZero = false; break; }
            if (allZero && fabs(a[i][n]) > EPS) { noSolution = true; break; }
        }

        if (noSolution) {
            cout << "No solution.\n\n";
            continue;
        }

        // Check for infinite solutions
        int rank = 0;
        for (int i = 0; i < n; i++)
            if (where[i] >= 0) rank++;

        if (rank < n) {
            cout << "Infinitely many solutions.\n\n";
            continue;
        }

        vector<double> x(n);
        for (int i = 0; i < n; i++) {
            if (where[i] >= 0)
                x[i] = a[where[i]][n] / a[where[i]][i];
        }

        for (int i = 0; i < n; i++) {
            cout << "x" << (i + 1) << "=" << fixed << setprecision(6) << x[i];
            if (i < n - 1) cout << ",";
        }
        cout << "\n\n";
    }
    return 0;
}
