#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector<int> queries(q);
    for (int i = 0; i < q; i++) cin >> queries[i];

    for (int i = 0; i < q; i++) {
        int k = queries[i];
        string t = s;

        int work_count = 0;
        for (char c : t) if (c == '0') work_count++;

        int used = 0;
        for (int j = 0; j < n && used < k; j++) {
            if (t[j] == '0') {
                t[j] = '1';
                used++;
            }
        }

        int pairs = 0;
        for (int j = 0; j < n - 1; j++) {
            if (t[j] == '1' && t[j + 1] == '1') pairs++;
        }

        cout << pairs << "\n";
    }

    return 0;
}
