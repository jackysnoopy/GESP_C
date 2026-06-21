#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(2 * n), b(2 * n);
        for (int i = 0; i < 2 * n; i++) cin >> a[i];
        for (int i = 0; i < 2 * n; i++) cin >> b[i];
        int wins = 0;
        vector<int> aNew(2 * n), bNew(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            aNew[i] = a[i];
            bNew[i] = b[i];
        }
        for (int i = 0; i < 2 * n; i++) {
            if (aNew[i] == 1 && bNew[i] == 2) wins++;
            else if (aNew[i] == 2 && bNew[i] == 3) wins++;
            else if (aNew[i] == 3 && bNew[i] == 1) wins++;
        }
        cout << wins << "\n";
        for (int i = 0; i < 2 * n; i++) {
            if (i > 0) cout << " ";
            cout << aNew[i];
        }
        cout << "\n";
        for (int i = 0; i < 2 * n; i++) {
            if (i > 0) cout << " ";
            cout << bNew[i];
        }
        cout << "\n";
    }
    return 0;
}
