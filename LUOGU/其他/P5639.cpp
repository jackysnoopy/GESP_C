#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int time = 0;
    int pos = 0;
    while (pos < n) {
        int parity = time % 2;
        int cnt = 0;
        while (pos < n && a[pos] == parity) {
            cnt++;
            pos++;
        }
        time++;
    }
    cout << time << "\n";
    return 0;
}
