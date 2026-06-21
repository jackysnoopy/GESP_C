#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> notes(n);
    for (int i = 0; i < n; i++) cin >> notes[i];

    sort(notes.begin(), notes.end());

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << notes[i];
    }
    cout << "\n";
    return 0;
}
