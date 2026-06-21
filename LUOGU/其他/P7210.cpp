#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Trie {
    int ch[26];
    bool isWord;
    Trie() { memset(ch, -1, sizeof(ch)); isWord = false; }
};
vector<Trie> trie(1);
void insert(const string& s) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (trie[u].ch[v] == -1) {
            trie[u].ch[v] = trie.size();
            trie.push_back(Trie());
        }
        u = trie[u].ch[v];
    }
    trie[u].isWord = true;
}
// Game: players alternate adding letters. Current prefix must be a prefix of some word.
// If it's a word, the player who just moved doesn't lose (the NEXT player might lose).
// A position is losing if all moves lead to winning positions for the opponent.
// A position is winning if there exists a move to a losing position.
// Nina goes first (player 0), Emilija second (player 1).
// At each trie node, the current player chooses a child.
// If no children available, current player loses.
// We need to compute win/lose for each node, considering whose turn it is.
// Turn alternates: root is Nina's turn, depth 1 is Emilija's turn, etc.
// But the game can visit any prefix, not just complete words.
// The constraint: after each move, the word must be a prefix of some word in the player's list.
// Nina can only move to prefixes of her words. Emilija to prefixes of her words.
// So we need two tries: one for Nina, one for Emilija.
int nina_trie[200005][26], emilija_trie[200005][26];
int nina_cnt, emilija_cnt;
bool nina_end[200005], emilija_end[200005];
void insert_nina(const string& s) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (nina_trie[u][v] == -1) {
            nina_trie[u][v] = nina_cnt++;
        }
        u = nina_trie[u][v];
    }
    nina_end[u] = true;
}
void insert_emilija(const string& s) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (emilija_trie[u][v] == -1) {
            emilija_trie[u][v] = emilija_cnt++;
        }
        u = emilija_trie[u][v];
    }
    emilija_end[u] = true;
}
// At Nina's turn at node u in Nina's trie:
// She can move to any child v. After her move, it's Emilija's turn.
// But the current word must also be a prefix of some Emilija word!
// So Nina can only move to a child v where the corresponding prefix exists in Emilija's trie.
// Similarly for Emilija.
// This is complex. Let me use a different approach.
// 
// Actually, re-reading: "每一次添加字母后的单词必须是该玩家最喜爱歌曲中某个单词的前缀"
// After adding a letter, the word must be a prefix of SOME word in the player's list.
// The word is shared (not per-player). Both players build the same word.
// So after Nina adds a letter, the word must be a prefix of some Nina word.
// After Emilija adds a letter, the word must be a prefix of some Emilija word.
// So the valid positions for Nina's turn are prefixes of Nina's words.
// The valid positions for Emilija's turn are prefixes of Emilija's words.
// But a prefix can be valid for both.
//
// Game state: (current word, whose turn).
// Nina's turn: word must be a prefix of some Nina word (empty word is always valid).
// Emilija's turn: word must be a prefix of some Emilija word.
//
// Nina can add any letter such that the new word is a prefix of some Nina word.
// Emilija can add any letter such that the new word is a prefix of some Emilija word.
//
// This is a game on the intersection of two tries.
// Let me build a combined state space.
//
// State: (nina_node, emilija_node, turn).
// But the word is the same for both! So the state is just (current_word, turn).
// The current word is a prefix of some Nina word (if turn is Nina) or some Emilija word (if turn is Emilija).
//
// Actually, the state is simpler: the current word w.
// On Nina's turn: w must be a prefix of some Nina word. Nina adds a letter c such that w+c is a prefix of some Nina word.
// On Emilija's turn: w must be a prefix of some Emilija word. Emilija adds a letter c such that w+c is a prefix of some Emilija word.
//
// So we need to know, for each word w, whether it's a valid state for Nina and/or Emilija.
// And for each valid state, what are the possible moves.
//
// Build Nina's trie and Emilija's trie. A word w is valid for Nina if w is a prefix of some Nina word (i.e., w is a node in Nina's trie).
// Similarly for Emilija.
//
// The game starts at the empty word (root), Nina's turn.
// Nina can move to any child of the root in Nina's trie.
// After Nina moves to child c, it's Emilija's turn, and the word is c.
// Emilija can move to any child of c in Emilija's trie (if c is a node in Emilija's trie).
// If c is not a node in Emilija's trie, Emilija can't move and loses.
//
// So the state is (nina_node, emilija_node) where nina_node represents the current word in Nina's trie,
// and emilija_node represents the current word in Emilija's trie.
// But the word is the SAME, so nina_node and emilija_node represent the same word.
// 
// Let me use a different representation: state = (word_string, turn).
// But word strings can be long. Instead, use (nina_idx, emilija_idx, turn).
// nina_idx: current position in Nina's trie (or -1 if word is not in Nina's trie).
// emilija_idx: current position in Emilija's trie (or -1 if word is not in Emilija's trie).
// turn: 0 = Nina, 1 = Emilija.
//
// Actually, since the word is the same, if we know the word, we know both trie positions.
// Let me just use the word length and the trie nodes.
//
// For efficiency, I'll use memoization.
// State: (nina_node, emilija_node, turn).
// Nina's turn: she can move to any child of nina_node in Nina's trie.
//   The new word is that child's prefix. Emilija's new node is the corresponding node in Emilija's trie.
// Emilija's turn: she can move to any child of emilija_node in Emilija's trie.
//   Nina's new node is the corresponding node in Nina's trie.
//
// To find Emilija's node given Nina's node and a letter:
// We need to know which node in Emilija's trie corresponds to the same prefix.
// This requires mapping between the two tries.
//
// Simpler approach: use the word itself as the state key. But words can be up to 200000 chars total.
// 
// Actually, let me use a combined trie. Insert all Nina words and all Emilija words into a single trie.
// Mark each node with whether it's a valid Nina prefix and/or Emilija prefix.
// Then the game state is just the node in the combined trie + whose turn it is.
// Nina can move to any child that's a valid Nina prefix.
// Emilija can move to any child that's a valid Emilija prefix.
//
// This is the cleanest approach.
int combined[200005][26];
bool isNina[200005], isEmilija[200005];
int combined_cnt;
void insert_combined(const string& s, bool nina, bool emilija) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (combined[u][v] == -1) {
            combined[u][v] = combined_cnt++;
        }
        u = combined[u][v];
        if (nina) isNina[u] = true;
        if (emilija) isEmilija[u] = true;
    }
}
// win[node][turn]: can the current player force a win?
// turn=0: Nina's turn. She can move to any child that's isNina.
// turn=1: Emilija's turn. She can move to any child that's isEmilija.
// If no valid moves, current player loses (returns false).
int memo[200005][2];
bool win(int node, int turn) {
    if (memo[node][turn] != -1) return memo[node][turn];
    bool& res = memo[node][turn];
    if (turn == 0) {
        // Nina's turn
        bool hasMove = false;
        bool allWin = true;
        for (int c = 0; c < 26; c++) {
            int v = combined[node][c];
            if (v != -1 && isNina[v]) {
                hasMove = true;
                if (!win(v, 1)) { allWin = false; break; }
            }
        }
        if (!hasMove) res = false;
        else res = !allWin;
    } else {
        // Emilija's turn
        bool hasMove = false;
        bool allWin = true;
        for (int c = 0; c < 26; c++) {
            int v = combined[node][c];
            if (v != -1 && isEmilija[v]) {
                hasMove = true;
                if (!win(v, 0)) { allWin = false; break; }
            }
        }
        if (!hasMove) res = false;
        else res = !allWin;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(combined, -1, sizeof(combined));
    memset(memo, -1, sizeof(memo));
    combined_cnt = 1;
    isNina[0] = true;
    isEmilija[0] = true;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert_combined(s, true, false);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        insert_combined(s, false, true);
    }
    // Root: both Nina and Emilija prefixes. Nina's turn.
    bool ninaWins = win(0, 0);
    cout << (ninaWins ? "Nina" : "Emilija") << endl;
    return 0;
}
