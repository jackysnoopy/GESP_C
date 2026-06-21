#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, C, P;
        cin >> N >> C >> P;
        vector<string> nouns, tverbs,iverbs,conjs;
        vector<string> all_nouns;
        for (int i = 0; i < N; i++) {
            string word, type;
            cin >> word >> type;
            if (type == "noun") { nouns.push_back(word); all_nouns.push_back(word); }
            else if (type == "transitive-verb") tverbs.push_back(word);
            else if (type == "intransitive-verb") iverbs.push_back(word);
            else conjs.push_back(word);
        }
        
        int nn = nouns.size(), tv = tverbs.size(), iv = iverbs.size(), cj = conjs.size();
        int commas = C, periods = P;
        
        // Greedy: maximize word count
        // Type 1 sentence: noun + intransitive verb. Uses 1 period.
        // Type 2 sentence: noun + transitive-verb + noun(s). Uses 1 period, commas = nouns_after_verb - 1.
        // Compound: two sentences joined by conjunction. Uses 1 conjunction, 2 periods (one for each sentence).
        // Wait, compound uses 1 conjunction and the periods are shared?
        // Re-reading: "Two sentences may be joined into a compound sentence if a conjunction is placed in between them. The resulting compound sentence cannot be further joined."
        // "Every sentence (or compound sentence, if two sentences are joined) must end with a period."
        // So a compound sentence: S1 + conjunction + S2 + period. Uses 1 period, 1 conjunction.
        // Two separate sentences: S1 + period + S2 + period. Uses 2 periods.
        
        // Strategy: use as many words as possible.
        // Type 2 sentences use more words per period.
        // Let's try to maximize words.
        
        // For type 2: noun + verb + noun1, noun2, ..., nounk
        // Uses: 1 noun + 1 verb + k nouns = k+1 nouns + 1 verb
        // Periods: 1. Commas: k-1.
        // Total nouns used: k+1. Total verbs: 1.
        
        // For type 1: noun + verb. Uses 1 noun + 1 intransitive verb. Periods: 1.
        
        // Let's try all combinations of type 1 and type 2 sentences.
        
        int best_words = 0;
        string best_output;
        
        // Try: use t2 type-2 sentences and t1 type-1 sentences
        // t2 uses: t2 * (1 + args) nouns, t2 verbs, t2 periods, t2 * (args-1) commas
        // t1 uses: t1 nouns, t1 intransitive verbs, t1 periods
        // Total periods: t2 + t1 (or if compound, t2 + t1 - 1 with 1 conjunction)
        // But compound sentences reduce period count.
        
        // For simplicity, try without compound sentences first.
        for (int t2 = 0; t2 <= min(tv, nn - 1); t2++) {
            // t2 type-2 sentences, each with some number of nouns after verb
            // Let's say each has a_i nouns after verb, sum a_i = total_extra_nouns
            // Total nouns used: t2 + total_extra_nouns
            // Commas used: total_extra_nouns - t2 (if each has at least 1)
            // Periods used: t2
            // Remaining: nn - t2 - total_extra_nouns nouns, iv intransitive verbs, periods: P - t2
            
            // For type 1 sentences: use remaining nouns and intransitive verbs
            int remaining_periods = P - t2;
            if (remaining_periods < 0) continue;
            
            // Try different total_extra_nouns values
            for (int extra = t2; extra <= nn - t2; extra++) {
                int commas_needed = extra - t2;
                if (commas_needed > C) continue;
                
                int nouns_used = t2 + extra;
                int remaining_nouns = nn - nouns_used;
                int t1 = min(min(remaining_nouns, iv), remaining_periods);
                int total_words = (t2 + extra + t2) + t1; // type2: t2*(1+1) + extra nouns, type1: t1*2
                // Actually: type2 uses t2 nouns (subjects) + extra nouns (objects) + t2 verbs = t2 + extra + t2
                // type1 uses t1 nouns + t1 intransitive verbs = t1 * 2
                total_words = t2 + extra + t2 + t1 * 2;
                
                if (total_words > best_words) {
                    best_words = total_words;
                    // Build output
                    string out;
                    int ni = 0; // noun index
                    int ti = 0; // transitive verb index
                    int ii = 0; // intransitive verb index
                    
                    // Type 2 sentences
                    for (int j = 0; j < t2; j++) {
                        if (j > 0) out += " ";
                        out += all_nouns[ni] + " " + tverbs[ti];
                        ti++;
                        ni++;
                        // Add objects
                        int obj_count = (j < extra % t2) ? (extra / t2 + 1) : (extra / t2);
                        // Simplify: distribute extra nouns evenly
                        int base = extra / t2;
                        int rem = extra % t2;
                        obj_count = base + (j < rem ? 1 : 0);
                        
                        for (int k = 0; k < obj_count; k++) {
                            if (k == 0) out += " " + all_nouns[ni];
                            else out += ", " + all_nouns[ni];
                            ni++;
                        }
                        out += ".";
                    }
                    
                    // Type 1 sentences
                    for (int j = 0; j < t1; j++) {
                        if (t2 > 0 || j > 0) out += " ";
                        out += all_nouns[ni] + " " + iverbs[ii] + ".";
                        ni++;
                        ii++;
                    }
                    
                    best_output = out;
                }
            }
        }
        
        cout << best_words << "\n";
        if (best_words > 0) cout << best_output << "\n";
        else cout << "\n";
    }
    return 0;
}
