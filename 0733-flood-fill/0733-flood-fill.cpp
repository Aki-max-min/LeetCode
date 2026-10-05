class Solution {
public:

    void dfs(vector<vector<int>>& image, int r, int c,
             int originalColor, int newColor) {

        int m = image.size();
        int n = image[0].size();

        // Outside the grid
        if (r < 0 || r >= m || c < 0 || c >= n)
            return;

        // If this cell is not the original color,
        // we don't want to change it
        if (image[r][c] != originalColor)
            return;

        // Change the color
        image[r][c] = newColor;

        // Visit 4 neighbours
        dfs(image, r - 1, c, originalColor, newColor); // up
        dfs(image, r + 1, c, originalColor, newColor); // down
        dfs(image, r, c - 1, originalColor, newColor); // left
        dfs(image, r, c + 1, originalColor, newColor); // right
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                   int sr, int sc, int color) {

        int originalColor = image[sr][sc];

        // If both colors are same, nothing to do
        if (originalColor == color)
            return image;

        dfs(image, sr, sc, originalColor, color);

        return image;
    }
};