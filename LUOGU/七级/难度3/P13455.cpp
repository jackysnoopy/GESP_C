#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int toMin(const string& s) {
    return ((s[0]-'0')*10 + (s[1]-'0')) * 60 + (s[3]-'0')*10 + (s[4]-'0');
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int turnaround;
        cin >> turnaround;
        int NA, NB;
        cin >> NA >> NB;
        vector<pair<int,int>> A, B;
        for (int i = 0; i < NA; i++) {
            string s, e; cin >> s >> e;
            A.push_back({toMin(s), toMin(e)});
        }
        for (int i = 0; i < NB; i++) {
            string s, e; cin >> s >> e;
            B.push_back({toMin(s), toMin(e)});
        }
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        // availA / availB: earliest ready time of a train waiting at A / B
        priority_queue<int, vector<int>, greater<int>> availA, availB;
        int ca = 0, cb = 0;
        int ia = 0, ib = 0;
        while (ia < (int)A.size() || ib < (int)B.size()) {
            bool takeA;
            if (ia >= (int)A.size()) takeA = false;
            else if (ib >= (int)B.size()) takeA = true;
            else takeA = (A[ia].first <= B[ib].first);
            if (takeA) {
                int d = A[ia].first, a = A[ia].second; ia++;
                if (!availA.empty() && availA.top() <= d) availA.pop();
                else ca++;
                availB.push(a + turnaround);
            } else {
                int d = B[ib].first, a = B[ib].second; ib++;
                if (!availB.empty() && availB.top() <= d) availB.pop();
                else cb++;
                availA.push(a + turnaround);
            }
        }
        cout << "Case #" << tc << ": " << ca << " " << cb << "\n";
    }
    return 0;
}
