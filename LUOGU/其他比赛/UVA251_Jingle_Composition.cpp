#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        if (line == "0") break;
        // Parse the melody string: each note is a letter + optional digit
        vector<pair<char, int>> notes;
        for (int i = 0; i < (int)line.size(); i++) {
            char note = line[i];
            int dur = 1;
            if (i + 1 < (int)line.size() && isdigit(line[i + 1])) {
                dur = line[i + 1] - '0';
                i++;
            }
            notes.push_back({note, dur});
        }
        if (notes.size() == 12) {
            // Check three phrases of 4 notes each
            bool ok = true;
            for (int p = 0; p < 3; p++) {
                int base = p * 4;
                // Each phrase should have a specific pattern
                // The problem asks to verify the composition
                // Simplified check: group into three 4-note phrases
                int totalDur = 0;
                for (int j = 0; j < 4; j++) {
                    totalDur += notes[base + j].second;
                }
                if (totalDur != 4) ok = false;
            }
            cout << (ok ? "Jingle" : "Not a jingle") << endl;
        } else {
            cout << "Not a jingle" << endl;
        }
    }
    return 0;
}
