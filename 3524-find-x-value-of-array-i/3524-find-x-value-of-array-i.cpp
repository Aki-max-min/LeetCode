class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            int x = num % k;

            vector<long long> newdp(k, 0);

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * x) % k;
                newdp[newRemainder] += dp[r];
            }

            // Start a new subarray with nums[i]
            newdp[x]++;

            // Add all subarrays ending here to the answer
            for (int r = 0; r < k; r++) {
                ans[r] += newdp[r];
            }

            dp = newdp;
        }

        return ans;
    }
};