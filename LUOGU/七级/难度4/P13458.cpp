#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C;
    cin >> C;

    for (int c = 1; c <= C; c++) {
        int N, M;
        cin >> N >> M;

        vector<vector<pair<int, int>>> customers(M);
        for (int i = 0; i < M; i++) {
            int T;
            cin >> T;
            for (int j = 0; j < T; j++) {
                int x, y;
                cin >> x >> y;
                customers[i].push_back({x, y});
            }
        }

        vector<int> result(N, 0);
        bool possible = true;

        for (int i = 0; i < M; i++) {
            bool satisfied = false;
            int malted = -1;
            for (auto& [flavor, type] : customers[i]) {
                if (result[flavor - 1] == type) {
                    satisfied = true;
                    break;
                }
                if (type == 1) malted = flavor - 1;
            }
            if (!satisfied) {
                if (malted == -1) {
                    possible = false;
                    break;
                }
                result[malted] = 1;
            }
        }

        cout << "Case #" << c << ": ";
        if (!possible) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (int i = 0; i < N; i++) {
                if (i) cout << " ";
                cout << result[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
