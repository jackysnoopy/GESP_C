#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    string extras;
    cin >> extras;
    string all = S + extras;
    sort(all.begin(), all.end());
    cout << all << "\n";
    return 0;
}
