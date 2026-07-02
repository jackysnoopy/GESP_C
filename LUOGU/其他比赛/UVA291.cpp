#include <iostream>
#include <vector>
using namespace std;

int ans = 0;
int rainbow[10] = {0};

void dfs(int pos, int count[]) {
    if (pos == 9) {
        ans++;
        return;
    }
    for (int i = 1; i <= 5; i++) {
        if (count[i] < 2 && (pos <= 1 || count[i] > 0)) {
            if (i > 1 && count[i - 1] == 0) continue;
            count[i]++;
            rainbow[pos] = i;
            dfs(pos + 1, count);
            count[i]--;
        }
    }
}

int main() {
    int count[6] = {0};
    dfs(0, count);
    cout << ans << endl;
    return 0;
}
