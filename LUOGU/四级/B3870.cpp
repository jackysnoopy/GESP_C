#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    cin >> N;
    if (N == 0) {
        cout << "00\n";
        return 0;
    }
    vector<int> bytes;
    while (N) {
        int b = N & 127;
        N >>= 7;
        if (N) b |= 128;
        bytes.push_back(b);
    }
    for (int i = 0; i < (int)bytes.size(); i++) {
        if (i) cout << " ";
        int hi = bytes[i] / 16, lo = bytes[i] % 16;
        cout << char(hi < 10 ? '0' + hi : 'A' + hi - 10);
        cout << char(lo < 10 ? '0' + lo : 'A' + lo - 10);
    }
    cout << "\n";
    return 0;
}
