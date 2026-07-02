#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    string line;
    while (getline(cin, line) && line != "#") {
        set<string> dictionary;
        dictionary.insert(line);
        while (getline(cin, line) && line != "#") {
            dictionary.insert(line);
        }
        
        string word;
        while (cin >> word && word != "#") {
            bool found = false;
            for (auto &dict : dictionary) {
                if (dict == word) {
                    found = true;
                    break;
                }
            }
            cout << word << " is " << (found ? "in" : "not in") << " the dictionary.\n";
        }
        cin.ignore();
    }
    return 0;
}
