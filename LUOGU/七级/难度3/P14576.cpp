#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> speed(n);
    for (int i = 0; i < n; i++) cin >> speed[i];

    int maxSpeed = *max_element(speed.begin(), speed.end());
    cout << maxSpeed << "\n";
    return 0;
}
