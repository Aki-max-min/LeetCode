#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int totalXOR = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            totalXOR ^= x;

            if (x != 0) {
                hasNonZero = true;
            }
        }

        // Entire array has non-zero XOR
        if (totalXOR != 0) {
            return n;
        }

        // Total XOR is 0, but there is a non-zero element.
        // Remove one non-zero element.
        if (hasNonZero) {
            return n - 1;
        }

        // All elements are 0
        return 0;
    }
};