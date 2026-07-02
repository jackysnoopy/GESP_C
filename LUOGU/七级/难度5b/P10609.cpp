#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

int n, m, c;
int a[MAXN][MAXN];
int R[MAXN], M[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++) cin >> R[i];
    for (int i = 1; i <= n; i++) cin >> M[i];

    int myKeep = -1;
    if (c == 0) {
        int bestVal = -2000000000;
        for (int i = 1; i <= n; i++) {
            if (R[i] == 0) continue;
            int worst = 2000000000;
            for (int j = 1; j <= n; j++) {
                if (M[j] == 0) continue;
                worst = min(worst, a[i][j]);
            }
            if (worst > bestVal) {
                bestVal = worst;
                myKeep = i;
            }
        }
    } else {
        int bestVal = 2000000000;
        for (int j = 1; j <= n; j++) {
            if (M[j] == 0) continue;
            int worst = -2000000000;
            for (int i = 1; i <= n; i++) {
                if (R[i] == 0) continue;
                worst = max(worst, a[i][j]);
            }
            if (worst < bestVal) {
                bestVal = worst;
                myKeep = j;
            }
        }
    }

    int totalDiscard = 2 * (m - 1);
    for (int turn = 0; turn < totalDiscard; turn++) {
        if (turn % 2 == 0) {
            if (c == 0) {
                for (int i = 1; i <= n; i++) {
                    if (R[i] > 0 && i != myKeep) {
                        cout << i << endl;
                        cout.flush();
                        R[i]--;
                        break;
                    }
                }
            } else {
                int oppDiscard;
                cin >> oppDiscard;
                if (oppDiscard == -1 || oppDiscard == 0) return 0;
                M[oppDiscard]--;
            }
        } else {
            if (c == 1) {
                for (int i = 1; i <= n; i++) {
                    if (M[i] > 0 && i != myKeep) {
                        cout << i << endl;
                        cout.flush();
                        M[i]--;
                        break;
                    }
                }
            } else {
                int oppDiscard;
                cin >> oppDiscard;
                if (oppDiscard == -1 || oppDiscard == 0) return 0;
                R[oppDiscard]--;
            }
        }
    }

    int result;
    cin >> result;
    return 0;
}
