#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    // 标记每个B是否被BC匹配使用
    vector<bool> b_used(n, false);

    // 第一遍：从右到左贪心匹配BC
    // 用栈维护可用的B的位置，遇到C就和最近（最右）的B配对
    vector<int> b_stack;
    int bc_match = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'B') {
            b_stack.push_back(i);
        } else if (s[i] == 'C') {
            if (!b_stack.empty()) {
                // 匹配BC：b_stack中的B在C的右边？不，从右到左扫描，
                // b_stack中的B的位置 > 当前C的位置，所以B在C后面，不符合要求
                // 等等，从右到左扫描时，先遇到的是右边的字符
                // B(4)先入栈，然后C(3)来了，B4在C3右边，即B在C后面
                // 但BC操作要求B在C前面（B的位置 < C的位置）
                // 所以从右到左扫描时，遇到C再匹配栈顶B，栈顶B的位置 > C的位置，
                // 这意味着B在C后面，不满足BC操作要求！
            }
        }
    }

    // 重新设计：从左到右贪心匹配BC也不对...
    // 让我重新思考

    // 正确做法：
    // 1. 从左到右贪心匹配BC（用栈维护B，遇到C就配对栈底最早的B）
    //    这样匹配的是最前面的B和C
    // 2. 剩余的B从左到右贪心匹配AB

    // 不对，从左到右匹配BC时，用栈的话是LIFO，配对的是最近的B。
    // 用队列的话是FIFO，配对的是最早的B。

    // 实际上，从右到左扫描时：
    // 遇到B就入栈，遇到C就看栈里有没有B。
    // 但此时栈里的B都在C的右边，不满足B在C前面的要求。

    // 正确的从右到左BC匹配：
    // 遇到C就入c_stack，遇到B就和c_stack配对
    // 这样B在C左边 ✓

    b_stack.clear();
    vector<int> c_stack;
    bc_match = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'C') {
            c_stack.push_back(i);
        } else if (s[i] == 'B') {
            if (!c_stack.empty()) {
                // B(i) 和 C(c_stack.top()) 配对，i < c_stack.top() ✓
                b_used[i] = true;
                c_stack.pop_back();
                bc_match++;
            }
        }
    }

    // 第二遍：从左到右贪心匹配AB，只用未被BC匹配的B
    int ab_match = 0;
    int a_count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            a_count++;
        } else if (s[i] == 'B' && !b_used[i]) {
            if (a_count > 0) {
                ab_match++;
                a_count--;
            }
        }
    }

    cout << ab_match + bc_match << "\n";
    return 0;
}
