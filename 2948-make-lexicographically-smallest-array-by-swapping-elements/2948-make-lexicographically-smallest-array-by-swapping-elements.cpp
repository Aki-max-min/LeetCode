class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store value and its original index
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            v.push_back({nums[i], i});
        }

        // Sort by values
        sort(v.begin(), v.end());

        int i = 0;

        while (i < n) {
            int j = i;

            // Find a connected group:
            // consecutive sorted values differ by <= limit
            while (j + 1 < n && v[j + 1].first - v[j].first <= limit) {
                j++;
            }

            // Collect original indices of this group
            vector<int> indices;
            vector<int> values;

            for (int k = i; k <= j; k++) {
                indices.push_back(v[k].second);
                values.push_back(v[k].first);
            }

            // Sort indices so smallest values go to smallest positions
            sort(indices.begin(), indices.end());

            // values are already sorted because v is sorted
            for (int k = 0; k < indices.size(); k++) {
                nums[indices[k]] = values[k];
            }

            i = j + 1;
        }

        return nums;
    }
};