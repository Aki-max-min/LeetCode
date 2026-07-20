class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        k %= total;

        vector<vector<int>> ans(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Current index in 1D
                int curr = i * n + j;

                // New index after shifting
                int next = (curr + k) % total;

                // Convert back to 2D
                ans[next / n][next % n] = grid[i][j];
            }
        }

        return ans;
    }
};