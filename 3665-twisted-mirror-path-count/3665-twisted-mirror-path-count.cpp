class Solution {
public:
    const int MOD = 1e9 + 7;

    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<long long>> dp(m, vector<long long>(n, 0));

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0)
                    continue;

                long long ways = dp[i][j];

                // Try moving right
                int x = i;
                int y = j + 1;
                int dir = 0; // 0 = right, 1 = down

                while (x < m && y < n && grid[x][y] == 1) {
                    if (dir == 0) {
                        x++;
                        dir = 1;
                    } else {
                        y++;
                        dir = 0;
                    }
                }

                if (x < m && y < n) {
                    dp[x][y] = (dp[x][y] + ways) % MOD;
                }

                // Try moving down
                x = i + 1;
                y = j;
                dir = 1;

                while (x < m && y < n && grid[x][y] == 1) {
                    if (dir == 1) {
                        y++;
                        dir = 0;
                    } else {
                        x++;
                        dir = 1;
                    }
                }

                if (x < m && y < n) {
                    dp[x][y] = (dp[x][y] + ways) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};