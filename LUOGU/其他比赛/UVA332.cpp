#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n) {
        vector<int> readings(n);
        for (int i = 0; i < n; i++) cin >> readings[i];

        vector<int> peaks;
        for (int i = 0; i < n; i++) {
            if ((i == 0 || readings[i] >= readings[i - 1]) &&
                (i == n - 1 || readings[i] >= readings[i + 1])) {
                peaks.push_back(readings[i]);
            }
        }

        cout << peaks.size();
        for (int i = 0; i < (int)peaks.size(); i++) {
            if (i % 10 == 0) cout << "\n";
            else cout << " ";
            cout << peaks[i];
        }
        cout << "\n\n";
    }
    return 0;
}
