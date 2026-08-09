class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        
        int n = piles.size();

        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = piles[i] + suffix[i + 1];
        }

        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        function<int(int, int)> solve = [&](int i, int M) {

            if (i >= n)
                return 0;

            if (i + 2 * M >= n)
                return suffix[i];

            if (dp[i][M] != -1)
                return dp[i][M];

            int ans = 0;

            for (int X = 1; X <= 2 * M; X++) {

                int taken = suffix[i] - suffix[i + X];

                int opponent = solve(i + X, max(M, X));

                int current = suffix[i] - opponent;

                ans = max(ans, current);
            }

            return dp[i][M] = ans;
        };

        return solve(0, 1);
    }
};