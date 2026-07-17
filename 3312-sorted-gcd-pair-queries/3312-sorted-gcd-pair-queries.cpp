#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        // cnt[d] = how many numbers are divisible by d
        vector<long long> cnt(mx + 1, 0);
        for (int d = 1; d <= mx; d++) {
            for (int j = d; j <= mx; j += d)
                cnt[d] += freq[j];
        }

        // exact[d] = number of pairs whose gcd is exactly d
        vector<long long> exact(mx + 1, 0);

        for (int d = mx; d >= 1; d--) {
            long long pairs = cnt[d] * (cnt[d] - 1) / 2;
            for (int j = 2 * d; j <= mx; j += d)
                pairs -= exact[j];
            exact[d] = pairs;
        }

        // Prefix count of sorted gcdPairs
        vector<long long> pref(mx + 1, 0);
        for (int i = 1; i <= mx; i++)
            pref[i] = pref[i - 1] + exact[i];

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            // Find first gcd value whose cumulative count > q
            int g = lower_bound(pref.begin() + 1, pref.end(), q + 1) - pref.begin();
            ans.push_back(g);
        }

        return ans;
    }
};