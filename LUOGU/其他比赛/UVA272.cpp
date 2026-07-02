#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    bool left = true;
    while (getline(cin, line)) {
        string result = "";
        for (char c : line) {
            if (c == '"') {
                if (left) {
                    result += "``";
                } else {
                    result += "''";
                }
                left = !left;
            } else {
                result += c;
            }
        }
        cout << result << "\n";
    }
    return 0;
}
