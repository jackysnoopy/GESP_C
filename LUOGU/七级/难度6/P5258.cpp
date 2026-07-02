#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> inDegree(n, 0);
    vector<int> outDegree(n, 0);
    
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        outDegree[x]++;
        inDegree[y]++;
    }
    
    int leaves = 0;
    for (int i = 0; i < n; i++) {
        if (outDegree[i] == 0) {
            leaves++;
        }
    }
    
    cout << leaves << endl;
    
    return 0;
}
