#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long gcd(long long a, long long b) {
    while (b) { long long t = b; b = a % b; a = t; }
    return a;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> num(n), den(n);
    for (int i = 0; i < n; i++) cin >> num[i] >> den[i];
    // We can divide all elements by any a_j repeatedly.
    // After dividing by a_j, the element a_i becomes a_i/a_j.
    // We want to minimize the minimum of the sequence.
    // 
    // Key: the minimum element in the sequence is min(a_i).
    // If we divide by the element with largest value, the minimum shrinks.
    // After dividing all by max, the new values are a_i/max.
    // The new min is min(a_i)/max.
    // Then we divide by the new max, which is max(a_i)/max.
    // Continue...
    // 
    // Actually we can choose any element to divide by at each step.
    // To minimize the minimum, we should always divide by the maximum.
    // After k steps of dividing by current max, the minimum becomes:
    // min(a) / (max * second_max * ... * kth_max)
    // Wait no. After step 1: divide all by max. New min = min/max. New max = 1 (old max/max).
    // After step 2: divide all by 1. New values unchanged. That's bad.
    // 
    // Better: divide by the current maximum at each step.
    // Step 1: max is M1. After division: all / M1. New values: a_i/M1.
    // The new max could be any a_j/M1 where a_j is original max.
    // Actually the new max is max(a)/M1 = 1. The new min is min(a)/M1.
    // If we divide by 1 next, nothing changes.
    // 
    // Hmm. So we should divide by elements that are NOT the current maximum of the sequence.
    // Wait, we divide by a specific element's value. After division by a_j:
    // - If a_j is the max, the new max becomes 1.
    // - If a_j is not the max, we can make the sequence smaller.
    // 
    // Actually I think the answer is simpler. The minimum value after any number of operations
    // is min(a_i * product(1/a_j for selected j's)).
    // We want to minimize this, which means we want to multiply min(a_i) by product(1/a_j).
    // To maximize product(1/a_j), we divide by the largest a_j's.
    // 
    // But after dividing, the elements change, and we divide by the NEW values.
    // This is getting complex. For difficulty 2, let me think of a simpler approach.
    // 
    // Actually: after dividing by a_j, ALL elements are divided by a_j.
    // So the ratios between elements stay the same!
    // a_i/a_j stays constant. Only the absolute values change.
    // After dividing by a_j, element k has value a_k/a_j.
    // After dividing by a_k/a_j (the new value of element k), element k has value 1.
    // 
    // So the minimum value after operations is:
    // min over j of a_j. But we can do better by chaining.
    // After dividing by a_j: all become a_k/a_j.
    // Then divide by a_m/a_j: all become (a_k/a_j) / (a_m/a_j) = a_k/a_m.
    // So we can effectively divide by any single element's ratio.
    // 
    // The minimum achievable value is min_{i,j} a_i/a_j = min(a)/max(a).
    // But we need to express this as a fraction.
    // min(a)/max(a) = min_num/max_den / (max_num/min_den) ... this gets complex with fractions.
    // 
    // Actually with fractions a_i = x_i/y_i:
    // a_i/a_j = (x_i/y_i) / (x_j/y_j) = x_i*y_j / (y_i*x_j)
    // min_{i,j} x_i*y_j / (y_i*x_j) = min_num * max_den / (min_den * max_num)
    // where min_num/y is the fraction with smallest value, max_num/y is the largest.
    
    // Find the fraction with minimum value and maximum value
    // a_i = x_i/y_i. To find min and max of fractions:
    // min: smallest x_i/y_i, i.e., x_i*y_j < x_j*y_i for all j
    // max: largest x_i/y_i
    long long minNum = num[0], minDen = den[0];
    long long maxNum = num[0], maxDen = den[0];
    for (int i = 1; i < n; i++) {
        // Compare num[i]/den[i] with minNum/minDen
        if (num[i] * minDen < minNum * den[i]) {
            minNum = num[i]; minDen = den[i];
        }
        if (num[i] * maxDen > maxNum * den[i]) {
            maxNum = num[i]; maxDen = den[i];
        }
    }
    // Answer: min / max = (minNum * maxDen) / (minDen * maxNum)
    long long ansNum = minNum * maxDen;
    long long ansDen = minDen * maxNum;
    long long g = gcd(ansNum, ansDen);
    ansNum /= g;
    ansDen /= g;
    cout << ansNum << " " << ansDen << "\n";
    return 0;
}
