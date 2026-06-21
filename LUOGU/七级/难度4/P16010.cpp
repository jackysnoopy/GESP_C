#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, G;
    cin >> N >> G;

    vector<vector<int>> grids(G, vector<int>(N * N));

    for (int g = 0; g < G; g++) {
        for (int i = 0; i < N; i++) {
            string row;
            cin >> row;
            for (int j = 0; j < N; j++) {
                grids[g][i * N + j] = (row[j] == 'R') ? 1 : 0;
            }
        }
    }

    int pairs = 0;
    for (int i = 0; i < G; i++) {
        for (int j = i + 1; j < G; j++) {
            bool similar = true;
            for (int k = 0; k < N * N; k++) {
                if (grids[i][k] != grids[j][k]) {
                    similar = false;
                    break;
                }
            }
            if (similar) pairs++;
        }
    }

    cout << pairs << "\n";
    return 0;
}
