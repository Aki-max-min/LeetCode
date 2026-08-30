class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0, maxIndex = 0;

        // Find indices of minimum and maximum elements
        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // Make sure minIndex <= maxIndex
        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        // Option 1: Remove both from the front
        int front = right + 1;

        // Option 2: Remove both from the back
        int back = n - left;

        // Option 3: Remove one from front and one from back
        int mixed = (left + 1) + (n - right);

        return min({front, back, mixed});
    }
};