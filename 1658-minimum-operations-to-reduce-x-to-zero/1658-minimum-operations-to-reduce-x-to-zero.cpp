class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        long long total = 0;
        for (int num : nums) {
            total += num;
        }

        long long target = total - x;

        // If target < 0, impossible
        if (target < 0) {
            return -1;
        }

        // If target == 0, remove everything
        if (target == 0) {
            return n;
        }

        int left = 0;
        long long sum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            // Shrink window if sum becomes too large
            while (sum > target && left <= right) {
                sum -= nums[left];
                left++;
            }

            // Found a subarray with sum = target
            if (sum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        // No valid subarray
        if (maxLen == -1) {
            return -1;
        }

        return n - maxLen;
    }
};