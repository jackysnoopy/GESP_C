#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 300005;
int n, q;
int a[MAXN];
int l[MAXN], r[MAXN];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= q; i++) scanf("%d %d", &l[i], &r[i]);
    
    // 对每个询问计算答案
    for (int i = 1; i <= q; i++) {
        int left = l[i], right = r[i];
        int len = right - left + 1;
        
        // 统计区间内每个值的出现次数
        map<int, int> cnt;
        for (int j = left; j <= right; j++) {
            cnt[a[j]]++;
        }
        
        int types = cnt.size();
        
        // 计算总多样性
        // 将相同值放在一起可以最小化总多样性
        long long ans = 0;
        vector<int> freq;
        for (auto& p : cnt) {
            freq.push_back(p.second);
        }
        
        // 贪心：每次将最少的值放在一起
        sort(freq.begin(), freq.end());
        
        int pos = 0;
        for (int f : freq) {
            // 这f个位置贡献的多样性
            for (int j = 0; j < f; j++) {
                ans += types;
                if (j < f - 1) {
                    // 后续位置会减少一种类型
                }
            }
            types--;
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}