#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    // Teleport connects x and y (bidirectional).
    // Options:
    // 1. Don't use teleport: distance = |a - b|
    // 2. Go a -> x, teleport to y, go y -> b: distance = |a-x| + |y-b|
    // 3. Go a -> y, teleport to x, go x -> b: distance = |a-y| + |x-b|
    // Answer = min of these three.
    int d1 = abs(a - b);
    int d2 = abs(a - x) + abs(y - b);
    int d3 = abs(a - y) + abs(x - b);
    cout << min(d1, min(d2, d3)) << "\n";
    return 0;
}
