#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int count_six(int x) {
    if (x == 0) return 0;
    int cnt = 0;
    while (x > 0) {
        if (x % 10 == 6) ++cnt;
        x /= 10;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // 计算每个数的6的个数
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        w[i] = count_six(a[i]);
    }
    
    // 统计权重<6的物品
    vector<int> light;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (w[i] >= 6) {
            ++ans; // 单独成组
        } else {
            light.push_back(w[i]);
        }
    }
    
    // 对light排序（从大到小）
    sort(light.begin(), light.end(), greater<int>());
    
    // 双指针配对
    int i = 0, j = light.size() - 1;
    while (i < j) {
        if (light[i] + light[j] >= 6) {
            ++ans;
            ++i;
            --j;
        } else {
            --j;
        }
    }
    
    // 剩下的物品（i==j或i>j），考虑三个物品组合
    // 剩下的物品是light[i..end]，实际上此时i可能指向最后一个未配对的物品
    // 我们需要检查剩下的物品是否可以三个一组
    // 由于我们是从大到小排序，剩下的物品权重较小
    // 我们可以尝试每三个一组
    vector<int> remaining;
    for (int k = i; k <= j; ++k) {
        remaining.push_back(light[k]);
    }
    // 注意：如果i>j，remaining为空
    // 对remaining从大到小排序（已经排好了）
    // 每三个一组
    for (int k = 0; k + 2 < remaining.size(); k += 3) {
        if (remaining[k] + remaining[k+1] + remaining[k+2] >= 6) {
            ++ans;
        } else {
            // 由于remaining是从大到小，后面的更小，无法达到6，直接break
            break;
        }
    }
    
    cout << ans << endl;
    return 0;
}