#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isQuirksome(int n, int k) {
    string s = to_string(n);
    while ((int)s.size() < k) s = "0" + s;
    int left = stoi(s.substr(0, k/2));
    int right = stoi(s.substr(k/2, k/2));
    return (left + right) * (left + right) == n;
}

int main() {
    int k;
    while (cin >> k) {
        int limit = 1;
        for (int i = 0; i < k; i++) limit *= 10;
        for (int n = 0; n < limit; n++) {
            if (isQuirksome(n, k)) {
                string s = to_string(n);
                while ((int)s.size() < k) s = "0" + s;
                cout << s << endl;
            }
        }
    }
    return 0;
}
