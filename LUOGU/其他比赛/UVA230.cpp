#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    string title;
    int t = 0;
    while (getline(cin, title) && title != "END") {
        if (t++) cout << "\n";
        vector<string> books;
        string line;
        while (getline(cin, line) && line != "END") {
            books.push_back(line);
        }
        int n = books.size();
        vector<string> sorted = books;
        sort(sorted.begin(), sorted.end());
        map<string, int> pos;
        for (int i = 0; i < n; i++) {
            pos[books[i]] = i;
        }
        cout << title << "\n\n";
        for (int i = 0; i < n; i++) {
            if (books[i] == sorted[i]) continue;
            int cur = pos[sorted[i]];
            while (cur > i) {
                swap(books[cur], books[cur - 1]);
                pos[books[cur]] = cur;
                pos[books[cur - 1]] = cur - 1;
                cout << "Move " << books[cur] << " from " << (cur + 1) << " to " << cur << "\n";
                cur--;
            }
        }
    }
    return 0;
}
