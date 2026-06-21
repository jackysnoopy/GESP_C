#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // For each adjacent pair (i, i+1):
    // Both hatched by day max(a[i], a[i+1]).
    // Eggs produced per day: 1 if opposite gender, 0 if same.
    // Number of days they can produce: max(0, t - max(a[i], a[i+1]))
    // But wait, "第t天及其之后不再下蛋" means:
    // Eggs produced on days max(a[i],a[i+1])+1, ..., t-1.
    // Count = max(0, t - max(a[i], a[i+1]) - 1 + 1) = max(0, t - max(a[i], a[i+1]))
    // Wait: "在每一天结束后" - at the end of each day.
    // Day 1 end, Day 2 end, ..., Day t-1 end. (Day t and after: no eggs)
    // So eggs produced from day max(a[i],a[i+1])+1 end to day t-1 end? 
    // Or from day max(a[i],a[i+1]) end?
    // 
    // From sample: pair (1,2): a=[1,2], max=2. 
    // Hint says eggs on day 2 end and day 3 end = 2 eggs.
    // t-1 = 3, so days 2 to 3 = 2 eggs = t - max = 4 - 2 = 2. ✓
    // Pair (2,3): max=3. Eggs on day 3 end = 1 egg = t - max = 4 - 3 = 1. ✓
    // 
    // So count per pair = max(0, t - max(a[i], a[i+1]))
    //
    // We assign genders. For pair (i,i+1):
    // If same gender: 0 eggs from this pair.
    // If opposite: count[i] eggs.
    //
    // We want to maximize total eggs by choosing genders.
    // This is: for each pair, choose to "activate" it (opposite gender) or not.
    // But genders are shared: gender[i] affects both pair (i-1,i) and (i,i+1).
    //
    // So it's a chain: for each pair, if we activate it, we get count[i] eggs.
    // Activating pair (i,i+1) means gender[i] != gender[i+1].
    // We want to select a subset of pairs to activate (flip genders) to maximize sum of counts.
    // This is: max weight independent set on a path... no, it's simpler.
    // It's: maximize sum of count[i] for activated pairs, where activation means flipping.
    //
    // Actually this is equivalent to: partition into segments of same-gender.
    // Each boundary between segments contributes count[i].
    // We want to choose boundaries to maximize sum of count[i].
    // This is just: select any subset of pairs! Because we can always assign genders
    // to satisfy any subset: just alternate at selected boundaries.
    // For example, if we select pairs 1 and 3: genders = M,F,M,F,...
    //
    // So the answer is simply the sum of all positive count[i] values!
    
    long long ans = 0;
    for (int i = 0; i + 1 < n; i++) {
        int days = t - max(a[i], a[i+1]);
        if (days > 0) ans += days;
    }
    cout << ans << "\n";
    return 0;
}
