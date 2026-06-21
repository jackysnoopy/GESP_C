#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> packets(n);
    for (int i = 0; i < n; i++) cin >> packets[i];

    int maxPacket = *max_element(packets.begin(), packets.end());
    cout << maxPacket << "\n";
    return 0;
}
