#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string a, b;
    cin >> a >> b;

    vector<int> l(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }

    for (int i = 0; i < m; i++) {
        int fl = 0;
        for (int j = l[i]; j <= r[i]; j++) {
            if (a[j] != b[j]) {
                if (a[j] == '0') fl = 1;
                break;
            }
        }
        if (fl) {
            for (int j = l[i]; j <= r[i]; j++) {
                swap(a[j], b[j]);
            }
        }
    }

    cout << a << "\n";
    return 0;
}
