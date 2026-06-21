#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int vowels = 0, consonants = 0, y_count = 0, ng_count = 0;

    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == 'A' || S[i] == 'E' || S[i] == 'I' || S[i] == 'O' || S[i] == 'U') {
            vowels++;
        } else if (S[i] == 'Y') {
            y_count++;
        } else if (S[i] == 'N' && i + 1 < (int)S.size() && S[i + 1] == 'G') {
            ng_count++;
            i++;
        } else {
            consonants++;
        }
    }

    int total_consonants = consonants + ng_count;
    int total_vowels = vowels + y_count;

    int syllables = min(total_consonants / 2, total_vowels);

    if (syllables == 0) {
        cout << "0\n";
    } else {
        cout << syllables * 3 << "\n";
    }

    return 0;
}
