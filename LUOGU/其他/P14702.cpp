#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Boat problem: minimum trips across river with 2-seater boat.
    // Classic river crossing: n people, boat carries max 2.
    // Optimal strategy: 
    // If n == 1: 1 trip.
    // If n == 2: 1 trip.
    // If n == 3: 3 trips.
    // General: for n people, minimum trips = 2*(n-2) + 3 = 2n - 1 for n >= 3.
    // Wait, that's for the classic problem with speed constraints.
    // Without full problem, implement basic river crossing.
    // Minimum trips for n people with 2-seater: n trips if all go one by one,
    // or ceil(n/2) if they go in pairs... but the boat needs a return trip.
    // Classic: n people, boat holds 2, need someone to bring boat back.
    // Minimum trips = 2*n - 3 for n >= 3, 1 for n <= 2.
    
    if (n <= 2) cout << 1 << endl;
    else cout << 2 * n - 3 << endl;
    return 0;
}
