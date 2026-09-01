class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();

        double sum = 0;

        // First window
        for(int i = 0; i < k; i++) {
            sum += nums[i];
        }

        double maxavg = sum / k;

        // Slide the window
        for(int i = k; i < n; i++) {
            sum += nums[i];       // add new element
            sum -= nums[i - k];   // remove old element

            maxavg = max(maxavg, sum / k);
        }

        return maxavg;
    }
};