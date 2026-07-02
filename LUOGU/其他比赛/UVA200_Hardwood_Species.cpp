#include <iostream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, int> cnt;
    int total = 0;
    string name;

    while (cin >> name) {
        cnt[name]++;
        total++;
    }

    cout << fixed << setprecision(4);
    for (auto& p : cnt) {
        cout << p.first << " " << (double)p.second / total * 100.0 << "\n";
    }

    return 0;
}
