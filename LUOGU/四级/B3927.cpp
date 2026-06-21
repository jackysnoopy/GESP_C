#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    map<string, string> dict;
    for (int i = 0; i < N; i++) {
        string a, b;
        cin >> a >> b;
        dict[a] = b;
    }
    string s;
    cin >> s;
    string word;
    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            word += c;
        } else {
            if (!word.empty()) {
                if (dict.count(word)) cout << dict[word];
                else cout << "UNK";
                word.clear();
            }
            cout << c;
        }
    }
    if (!word.empty()) {
        if (dict.count(word)) cout << dict[word];
        else cout << "UNK";
    }
    cout << "\n";
    return 0;
}
