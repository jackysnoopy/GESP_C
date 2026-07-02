#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        int n = stoi(line);
        vector<vector<bool>> R(n + 1, vector<bool>(n + 1, false));
        vector<vector<bool>> S(n + 1, vector<bool>(n + 1, false));

        int i, j;
        while (cin >> i >> j && (i != 0 || j != 0)) {
            R[i][j] = true;
        }
        while (cin >> i >> j && (i != 0 || j != 0)) {
            S[i][j] = true;
        }
        cin.ignore();

        vector<vector<bool>> T(n + 1, vector<bool>(n + 1, false));
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (S[a][b]) {
                    for (int c = 1; c <= n; ++c) {
                        if (R[b][c]) {
                            T[a][c] = true;
                        }
                    }
                }
            }
        }

        cout << "\n";
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (T[a][b]) {
                    cout << a << " " << b << "\n";
                }
            }
        }
        cout << "\n";
    }

    return 0;
}