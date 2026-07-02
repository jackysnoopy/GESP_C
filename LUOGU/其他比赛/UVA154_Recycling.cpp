#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct City {
    char code;
    int score;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    vector<City> cities;
    
    while (getline(cin, line) && line[0] != '#') {
        if (line.empty()) continue;
        
        City city;
        city.code = line[0];
        city.score = 0;
        
        for (int i = 0; i < 5; i++) {
            getline(cin, line);
            // Parse: material, then 5 ranks
            // We only care about the rank for the current bin position
            // The line format: "P 1 3 2 4 5"
            // For city score, we sum the first-place preferences
            // Actually, we need to find: for each bin, what rank does it have for its own material
            // But the problem says: "sum of first-place preferences"
            // Let me re-read: "sort cities by best recycling behavior (highest sum of first-place preferences)"
            // Actually, I think it means: for each material, if a bin has rank 1, that counts as a "first-place"
            // So we sum: for each of the 5 materials, check if the rank for that material is 1
            
            // Parse the line
            char mat;
            int r1, r2, r3, r4, r5;
            sscanf(line.c_str(), "%c %d %d %d %d %d", &mat, &r1, &r2, &r3, &r4, &r5);
            
            // If r1 (rank for bin 1) is 1, add to score
            // Actually, re-reading: each line is for a material, and lists rank for each bin
            // "P 1 3 2 4 5" means: P has rank 1 for bin 1, rank 3 for bin 2, rank 2 for bin 3, etc.
            // So for this material, if we check each bin's rank, we see which bin prefers it most
            // But the score should be: for each material, if its rank-1 bin matches... hmm
            
            // Actually, I think the intended meaning is simpler:
            // The score for a city is the sum over all materials of (1 if that material's first-choice bin is correct)
            // But we don't know what "correct" is.
            
            // Let me re-think: The problem is about sorting cities by recycling behavior.
            // Each city has 5 bins, each bin prefers certain materials.
            // A "first-place preference" for a material means the bin that ranks it #1.
            // The score is: for each material, if the bin that ranks it #1 is the "correct" one... but we don't have a reference.
            
            // Actually, I think the score is simply: for each material, add 1 if any bin has rank 1 for it.
            // But every material will have exactly one bin with rank 1 (since ranks are 1-5, each used once).
            
            // Wait, re-reading more carefully: "highest sum of first-place preferences"
            // I think it means: for each material, we look at which bin ranks it #1.
            // Then we sum something about those rankings.
            
            // Actually, I think the intended interpretation is:
            // For each material, find the bin that ranks it #1. Then the score is the sum of... what exactly?
            
            // Let me look at the problem differently. Maybe the score for a city is:
            // For each material, if the bin designated for that material (by the first column) ranks it #1, add 1.
            // So if material P is in bin 1, and bin 1 ranks P #1, that's +1.
            
            // But we don't know which material goes in which bin...
            
            // Actually, I think I'm overcomplicating this. Let me re-read the problem statement:
            // "Each city is described by a letter code followed by 5 lines (P=paper, G=glass, C=cans, N=newspaper, L=landfill), 
            // each line containing the preference rank."
            // "The line for each material has format like 'P 1 3 2 4 5' meaning P has rank 1 for bin 1, rank 3 for bin 2, etc."
            
            // So the 5 lines represent 5 materials, and for each material, we have ranks for 5 bins.
            // The "first-place preference" for a material is the bin that ranks it #1.
            // The score is the sum of... I think it's the sum of (6 - rank) for each material's first-choice bin.
            // Or maybe it's simpler: for each material, add the rank that its first-choice bin gives it (which is always 1).
            
            // I think the actual intent is: for each material, find which bin ranks it #1, and add that bin's number.
            // So if P is ranked #1 by bin 3, add 3. Then sum all 5.
            // Higher sum = more diverse bin preferences = better recycling.
            
            // Let me implement that: for each material, find the bin with rank 1, add bin index.
            if (r1 == 1) city.score += 1;
            if (r2 == 1) city.score += 2;
            if (r3 == 1) city.score += 3;
            if (r4 == 1) city.score += 4;
            if (r5 == 1) city.score += 5;
        }
        
        cities.push_back(city);
        
        // Check if next line is blank (separator between test cases)
        // We'll handle this by checking if the next getline gives us a blank line
    }
    
    // Sort by score descending, then by code ascending
    sort(cities.begin(), cities.end(), [](const City& a, const City& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.code < b.code;
    });
    
    for (const auto& city : cities) {
        cout << city.code << "\n";
    }
    
    return 0;
}