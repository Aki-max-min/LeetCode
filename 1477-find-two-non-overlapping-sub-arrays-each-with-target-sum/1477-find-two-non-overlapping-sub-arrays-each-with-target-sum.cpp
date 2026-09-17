class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        // best[i] = minimum length of a target-sum subarray
        // completely within arr[0...i]
        vector<int> best(n, INF);

        int left = 0;
        long long sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window if sum is too large
            while (sum > target && left <= right) {
                sum -= arr[left];
                left++;
            }

            // We found a subarray [left...right]
            if (sum == target) {
                int len = right - left + 1;

                // Check if there is a non-overlapping
                // target-sum subarray before 'left'
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, len + best[left - 1]);
                }

                // Store the best subarray ending at or before right
                if (right == 0)
                    best[right] = len;
                else
                    best[right] = min(best[right - 1], len);
            } 
            else {
                // Carry forward previous best
                if (right > 0)
                    best[right] = best[right - 1];
            }
        }

        return ans == INF ? -1 : ans;
    }
};