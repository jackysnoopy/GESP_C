/**
 * UVA107 - The Cat in the Hat
 * 帽子里的猫
 *
 * 题意：
 *   戴帽子的猫（主猫）下面有W个工人猫，每个工人猫又有W个工人猫，
 *   如此递归。给定N（不含主猫的工人数）和H（树高），求：
 *   1. 没有工人的猫的数量（底层猫）
 *   2. 总工作量（第i层的猫贡献i单位工作量）
 *
 * 数学关系：
 *   N = W + W^2 + ... + W^(H-1)  （不含主猫的工人数）
 *   非工作猫数 = W^H
 *   总工作量 = sum(i * W^i, i=1..H)
 *
 * 解法：对W进行二分搜索，使等比数列之和等于N
 */
#include <iostream>

using namespace std;

int main() {
    long long N, H;

    while (cin >> N >> H) {
        if (N == 0 && H == 0) break;

        // 特殊情况处理
        if (H == 1) {
            // H=1时，N=W，非工作猫=W^1=W=N，总工作量=1*N
            cout << N << " " << N << endl;
            continue;
        }

        if (N == 0) {
            cout << "0 0" << endl;
            continue;
        }

        // 二分搜索求W：使得 W + W^2 + ... + W^(H-1) = N
        long long W = 1;
        long long lo = 1, hi = N;

        while (lo <= hi) {
            long long mid = (lo + hi) / 2;
            long long sum = 0;
            long long power = 1;
            bool overflow = false;

            for (int i = 1; i <= (int)H - 1; i++) {
                if (power > N / mid) {
                    overflow = true;
                    break;
                }
                power *= mid;
                if (sum > N - power) {
                    overflow = true;
                    break;
                }
                sum += power;
            }

            if (overflow || sum > N) {
                hi = mid - 1;
            } else if (sum < N) {
                lo = mid + 1;
            } else {
                W = mid;
                break;
            }
        }

        // 计算底层没有工人的猫的数量：W^H
        long long noWorkCats = 1;
        for (int i = 0; i < (int)H; i++) {
            noWorkCats *= W;
        }

        // 计算总工作量：sum_{i=1}^{H} i * W^i
        long long totalWork = 0;
        long long power = 1;
        for (int i = 1; i <= (int)H; i++) {
            power *= W;
            totalWork += (long long)i * power;
        }

        cout << noWorkCats << " " << totalWork << endl;
    }

    return 0;
}
