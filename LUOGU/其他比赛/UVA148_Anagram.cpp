#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool isAnagram(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;
    
    vector<int> count1(26, 0), count2(26, 0);
    for (char c : word1) count1[c - 'A']++;
    for (char c : word2) count2[c - 'A']++;
    
    return count1 == count2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    vector<string> dictionary;
    
    while (getline(cin, line) && line != "") {
        dictionary.push_back(line);
    }
    
    vector<string> test_words;
    while (getline(cin, line)) {
        test_words.push_back(line);
    }
    
    for (const string& test_word : test_words) {
        cout << test_word << ": ";
        
        vector<string> anagrams;
        for (const string& dict_word : dictionary) {
            if (dict_word != test_word && isAnagram(test_word, dict_word)) {
                anagrams.push_back(dict_word);
            }
        }
        
        for (size_t i = 0; i < anagrams.size(); ++i) {
            if (i > 0) cout << " ";
            cout << anagrams[i];
        }
        cout << endl;
    }
    
    return 0;
}
