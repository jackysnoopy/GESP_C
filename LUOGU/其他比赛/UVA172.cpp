#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[101][101];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        bool ok = true;
        for (int i = 0; i < n && ok; i++)
            for (int j = 0; j < n && ok; j++)
                if (a[i][j] != a[j][i] || (i == j && a[i][j] != 0))
                    ok = false;
        cout << (ok ? "true" : "false") << endl;
    }
    return 0;
}
