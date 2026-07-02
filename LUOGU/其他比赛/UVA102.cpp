/**
 * UVA102 - Ecological Bin Packing
 * 生态包装
 *
 * 题意：
 *   有三个箱子，每个箱子装有三种颜色的瓶子（棕色B、透明C、绿色G）。
 *   需要对三个箱子重新排列，使得所有同色瓶子集中到同一个箱子中。
 *   求最小移动次数，并输出对应的颜色排列（字典序最小）。
 *
 * 解法：
 *   枚举6种排列（3!），对每种排列计算需要移动的瓶子数。
 *   移动数 = 总瓶数 - 不需要移动的瓶子数（即已经在正确位置的瓶子）。
 *   选择移动次数最少的排列，若有多个则选字典序最小的。
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int bins[3][3];
    string colors = "BCG";

    while (cin >> bins[0][0] >> bins[0][1] >> bins[0][2] >>
                 bins[1][0] >> bins[1][1] >> bins[1][2] >>
                 bins[2][0] >> bins[2][1] >> bins[2][2]) {

        // 枚举6种排列：哪个箱子放B、哪个放C、哪个放G
        string perms[6] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};
        int bestMove = INT_MAX;
        string bestPerm = "";

        for (int p = 0; p < 6; p++) {
            string perm = perms[p];
            // perm[0]表示放B的箱子索引，perm[1]放C，perm[2]放G
            int moved = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (colors[j] != perm[i]) {
                        moved += bins[i][j];
                    }
                }
            }
            if (moved < bestMove) {
                bestMove = moved;
                bestPerm = perm;
            }
        }

        cout << bestPerm << " " << bestMove << endl;
    }

    return 0;
}
