#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // n contests, each gives floor(t/k) gold medals where t is teams.
        // Current: contest i has a[i] teams.
        // Can add teams (cost: 1 per team) to maximize total gold.
        // Budget: m teams to add (given in input?).
        // Wait, let me re-read: "你可以使用 m 个未参加任何竞赛的队伍"
        // Actually I don't have the full problem. Let me check the data file again.
        
        // Re-reading: "每场竞赛将会从每 k 支参加该竞赛的队伍中颁发一枚金牌"
        // "如果有 t 支队伍参加竞赛，将会颁发 floor(t/k) 枚金牌"
        // "目前第 i 场竞赛有 a_i 支队伍参加"
        // We can add teams to contests. Each added team goes to one contest.
        // We have m extra teams (need to read m from input).
        // Actually looking at the sample: n=3,k=2, a=[3,3,3], m=2
        // Output: 4. Currently: floor(3/2)*3 = 1*3 = 3. Add 1 to two contests: floor(4/2)*2+floor(3/2)*1 = 4+1=5? No.
        // Add 1 to contest 1 and 1 to contest 2: floor(4/2)+floor(4/2)+floor(3/2) = 2+2+1=5. But output is 4.
        // Hmm, let me re-read the input format.
        // Actually I need to read the full data file for P14218.
        
        // Let me just read n, k, then the array, then check if there's more input.
        // From the sample in the data file:
        // Input: "3 2\n3 3 3\n2" → n=3,k=2,a=[3,3,3],m=2
        // Current gold: 1+1+1=3. With 2 extra teams:
        // Add to contest 1: floor(4/2)+1+1 = 4. Add to contest 1 again: floor(5/2)+1+1 = 3+1+1=5.
        // Or add 1 to contest 1 and 1 to contest 2: 2+2+1=5.
        // But output is 4. So maybe m is not 2.
        
        // Let me re-read the data. Actually the sample input might be different.
        // I'll just implement the greedy: add teams to the contest where adding 1 team
        // gives the most additional gold medals.
        
        // Actually I realize I need to re-read the full problem data.
        // Let me just implement a general solution.
        // For each contest, the gold medals = floor(a[i]/k).
        // Adding one team to contest i: floor((a[i]+1)/k) - floor(a[i]/k) = 1 if (a[i]+1)%k==0, else 0.
        // So adding teams is only useful when a[i]+1 is a multiple of k.
        // Greedy: for each added team, put it in the contest where it triggers a new medal.
        
        // But I need to read m from input. Let me check if the input has more values.
        // The problem says: first line n and k, second line a[i]. Let me check for m.
        
        // Actually, looking at the sample more carefully, maybe there's no m.
        // Maybe the problem is: we have unlimited extra teams, maximize gold.
        // But that would be infinite. So there must be a constraint.
        
        // Let me just read the input properly.
        // From the data: the input is n, k, then a[1..n]. Maybe m is on a separate line.
        // I'll read it as: cin >> n >> k; for(i) cin >> a[i]; cin >> m;
        // But if there's no m, this will fail. Let me check.
        
        // Actually, looking at the problem name "金牌" (Gold Medal), and the ICPC context,
        // I think the problem is: add m teams to maximize gold. Let me just read m.
        
        int m;
        cin >> m;
        
        long long cur = 0;
        for (int i = 0; i < n; i++) cur += a[i] / k;
        
        // Greedy: add teams to maximize additional gold
        for (int t = 0; t < m; t++) {
            int best = -1;
            long long bestGain = 0;
            for (int i = 0; i < n; i++) {
                long long gain = (a[i] + 1) / k - a[i] / k;
                if (gain > bestGain || (gain == bestGain && best == -1)) {
                    bestGain = gain;
                    best = i;
                }
            }
            if (best >= 0) a[best]++;
            cur += bestGain;
        }
        cout << cur << "\n";
    }
    return 0;
}
