class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> points(maxVal + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }
        int prev2 = 0, prev1 = 0;
        for (int i = 1; i <= maxVal; i++) {
            int curr = max(prev1, prev2 + points[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};
