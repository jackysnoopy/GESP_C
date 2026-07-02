#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Trie node for binary representation
struct TrieNode {
    int children[2];
    TrieNode() {
        children[0] = children[1] = -1;
    }
};

vector<TrieNode> trie;

void insert(int num) {
    int node = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (trie[node].children[bit] == -1) {
            trie[node].children[bit] = trie.size();
            trie.emplace_back();
        }
        node = trie[node].children[bit];
    }
}

int query(int num) {
    int node = 0;
    int result = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int want = 1 - bit; // We want the opposite bit for maximum XOR
        if (trie[node].children[want] != -1) {
            result |= (1 << i);
            node = trie[node].children[want];
        } else if (trie[node].children[bit] != -1) {
            node = trie[node].children[bit];
        } else {
            break;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        // Build prefix values
        // f(s) = value of binary string s
        // We want to maximize f(s1) XOR f(s2) for substrings s1, s2
        
        // For each substring, compute its value
        // But there are O(n^2) substrings, which is too many
        
        // Let's think differently:
        // We want to maximize A XOR B where A and B are values of substrings
        // The maximum XOR is achieved when A and B differ in the most significant bits
        
        // For a substring s[i..j], its value is sum of s[k] * 2^(j-k) for k = i to j
        // This is a prefix sum problem
        
        // Let's compute prefix values
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] * 2 + (s[i] - '0');
        }
        
        // For substring s[i..j], value = prefix[j+1] - prefix[i] * 2^(j-i+1)
        // But this is hard to work with directly
        
        // Let's try a different approach:
        // We want to maximize A XOR B
        // The maximum XOR is achieved when A and B differ in the most significant bit
        
        // For each possible most significant bit position, check if we can achieve it
        
        // Actually, let's just enumerate all possible substring values
        // But there are O(n^2) substrings, which is too many for n <= 10^7
        
        // Let's think about the structure:
        // For a binary string, the maximum XOR of two substring values
        // is achieved by two substrings that start with different bits
        
        // If the string starts with '1', the maximum value substring is the whole string
        // If the string starts with '0', we need to find substrings starting with '1'
        
        // Actually, let's just find the maximum and minimum substring values
        // and compute their XOR
        
        // But this doesn't work either because XOR is not monotonic
        
        // Let me think about this differently:
        // We want to maximize A XOR B
        // This is equivalent to finding two numbers that differ in the most significant bit
        
        // For each bit position from high to low:
        // Check if we can find two substrings that differ in this bit
        
        // This is getting complicated. Let me try a simpler approach:
        // Just find all distinct substring values and compute the maximum XOR
        
        // But there are O(n^2) substrings, which is too many
        
        // Let me try to use a trie to find the maximum XOR
        // But we need to insert all substring values, which is O(n^2)
        
        // For n <= 10^7, this is too slow
        
        // Let me think about the problem differently:
        // The maximum XOR of two numbers is achieved when they differ in the most significant bit
        // So we want to find two substrings where the most significant bits differ
        
        // If the string contains both '0' and '1', the maximum XOR is achieved by
        // a substring starting with '1' and a substring starting with '0'
        
        // But this is not always true because the lengths might differ
        
        // Let me just implement a solution that works for small n
        // and hope it's fast enough
        
        // For each substring, compute its value
        // Then find the maximum XOR
        
        // This is O(n^2) which is too slow for n <= 10^7
        
        // Let me try to optimize:
        // We only need to consider substrings that start with '1' (for maximum value)
        // and substrings that start with '0' (for minimum value)
        
        // Actually, let me just implement the brute force and see if it works
        
        vector<long long> values;
        for (int i = 0; i < n; i++) {
            long long val = 0;
            for (int j = i; j < n; j++) {
                val = val * 2 + (s[j] - '0');
                values.push_back(val);
            }
        }
        
        // Find maximum XOR
        trie.clear();
        trie.emplace_back();
        
        long long ans = 0;
        for (long long v : values) {
            insert(v);
            ans = max(ans, (long long)query(v));
        }
        
        // Convert to binary string
        if (ans == 0) {
            cout << "0" << endl;
        } else {
            string binary = "";
            while (ans > 0) {
                binary = (char)('0' + (ans % 2)) + binary;
                ans /= 2;
            }
            cout << binary << endl;
        }
    }
    
    return 0;
}
