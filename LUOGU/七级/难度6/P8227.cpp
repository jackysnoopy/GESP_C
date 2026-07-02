#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    
    string A, B;
    cin >> A >> B;
    
    // 计算括号序列的深度
    auto getDepth = [](const string& s) {
        vector<int> depth(s.size());
        int cur = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                cur++;
                depth[i] = cur;
            } else {
                depth[i] = cur;
                cur--;
            }
        }
        return depth;
    };
    
    vector<int> depthA = getDepth(A);
    vector<int> depthB = getDepth(B);
    
    // 计算每个位置的深度差
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(depthA[i] - depthB[i]);
    }
    
    printf("%lld\n", ans / 2);
    return 0;
}