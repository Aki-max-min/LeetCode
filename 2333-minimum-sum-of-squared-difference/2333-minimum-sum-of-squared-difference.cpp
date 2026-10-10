class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<int> diff(n);
        long long total_diff = 0;
        int max_diff = 0;
        long long k = (long long)k1 + k2;

        for (int i = 0; i < n; ++i) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total_diff += diff[i];
            max_diff = max(max_diff, diff[i]);
        }

        if (total_diff <= k) return 0;

        int left = 0, right = max_diff;
        int limit = max_diff;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long operations_needed = 0;

            for (int d : diff) {
                if (d > mid) {
                    operations_needed += (d - mid);
                }
            }

            if (operations_needed <= k) {
                limit = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (diff[i] > limit) {
                k -= (diff[i] - limit);
                diff[i] = limit;
            }
        }

        for (int i = 0; i < n && k > 0; ++i) {
            if (diff[i] == limit) {
                diff[i]--;
                k--;
            }
        }

        long long ans = 0;
        for (int d : diff) {
            ans += 1LL * d * d;
        }

        return ans;
    }
};