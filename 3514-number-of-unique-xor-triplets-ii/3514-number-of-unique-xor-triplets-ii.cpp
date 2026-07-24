class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int val : nums) {
            vector<vector<bool>> ndp = dp; // choosing this index 0 times

            for (int cnt = 0; cnt <= 3; cnt++) {
                for (int xr = 0; xr < MAXX; xr++) {
                    if (!dp[cnt][xr]) continue;

                    for (int take = 1; take <= 3 && cnt + take <= 3; take++) {
                        int add = (take & 1) ? val : 0;
                        ndp[cnt + take][xr ^ add] = true;
                    }
                }
            }

            dp.swap(ndp);
        }

        int ans = 0;
        for (int xr = 0; xr < MAXX; xr++) {
            if (dp[3][xr]) ans++;
        }
        return ans;
    }
};