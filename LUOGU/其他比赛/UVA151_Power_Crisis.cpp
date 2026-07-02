#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N != 0) {
        for (int m = 2; ; ++m) {
            vector<int> cities(N);
            for (int i = 0; i < N; ++i) cities[i] = i + 1;

            int idx = 0;
            while (cities.size() > 1) {
                idx = (idx + m - 1) % cities.size();
                cities.erase(cities.begin() + idx);
            }
            if (cities[0] == 13) {
                cout << m << "\n";
                break;
            }
        }
    }

    return 0;
}
