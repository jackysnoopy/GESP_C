#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            int val = 0;
            for (int j = 0; j < n; j++) {
                val += a[j] * b[(j + i) % n];
            }
            cout << val;
        }
        cout << endl;
    }
    return 0;
}
