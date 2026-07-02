#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

string toLower(string s) {
    for (auto &c : s) c = tolower(c);
    return s;
}

int main() {
    string word;
    map<string, vector<string>> groups;
    while (cin >> word && word != "#") {
        string key = toLower(word);
        sort(key.begin(), key.end());
        groups[key].push_back(word);
    }
    vector<string> result;
    for (auto &p : groups) {
        if (p.second.size() == 1) {
            result.push_back(p.second[0]);
        }
    }
    sort(result.begin(), result.end());
    for (auto &w : result) {
        cout << w << "\n";
    }
    return 0;
}
