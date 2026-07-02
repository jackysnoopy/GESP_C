#include <iostream>
#include <string>
using namespace std;

int main() {
    int k = 1;
    while (true) {
        int R, C;
        cin >> R >> C;
        if (R == 0 && C == 0) break;
        if (k > 1) cout << endl;
        cout << "Reference " << k++ << endl;
        char grid[100][100];
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                cin >> grid[i][j];
        cout << "Queries" << endl;
        for (int q = 0; q < 10; q++) {
            int qr, qc;
            cin >> qr >> qc;
            bool found = false;
            for (int i = 0; i < R && !found; i++) {
                for (int j = 0; j < C && !found; j++) {
                    if (grid[i][j] == 'B') {
                        int dr = abs(qr - i);
                        int dc = abs(qc - j);
                        if ((dr == 0 && dc <= 2) ||
                            (dc == 0 && dr <= 2) ||
                            (dr <= 1 && dc <= 1)) {
                            found = true;
                        }
                    }
                }
            }
            cout << (found ? "Yes" : "No") << endl;
        }
    }
    return 0;
}
